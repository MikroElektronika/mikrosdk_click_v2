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
 * @file compass6.h
 * @brief This file contains API for Compass 6 Click Driver.
 */

#ifndef COMPASS6_H
#define COMPASS6_H

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
 * @addtogroup compass6 Compass 6 Click Driver
 * @brief API for configuring and manipulating Compass 6 Click driver.
 * @{
 */

/**
 * @defgroup compass6_reg Compass 6 Registers List
 * @brief List of registers of Compass 6 Click driver.
 */

/**
 * @addtogroup compass6_reg
 * @{
 */

/**
 * @brief Compass 6 description register.
 * @details Specified register for description of Compass 6 Click driver.
 */
#define COMPASS6_REG_SELFTEST_RSP       0x0C
#define COMPASS6_REG_INFO_VERSION       0x0D
#define COMPASS6_REG_INFO_ALPS          0x0E
#define COMPASS6_REG_WHO_I_AM           0x0F
#define COMPASS6_REG_OUTPUT_X_LSB       0x10
#define COMPASS6_REG_OUTPUT_X_MSB       0x11
#define COMPASS6_REG_OUTPUT_Y_LSB       0x12
#define COMPASS6_REG_OUTPUT_Y_MSB       0x13
#define COMPASS6_REG_OUTPUT_Z_LSB       0x14
#define COMPASS6_REG_OUTPUT_Z_MSB       0x15
#define COMPASS6_REG_STATUS             0x18
#define COMPASS6_REG_FIFO_PTR_STATUS    0x19
#define COMPASS6_REG_CTRL1              0x1B
#define COMPASS6_REG_CTRL2              0x1C
#define COMPASS6_REG_CTRL3              0x1D
#define COMPASS6_REG_CTRL4              0x1E
#define COMPASS6_REG_OFFSET_X_LSB       0x20
#define COMPASS6_REG_OFFSET_X_MSB       0x21
#define COMPASS6_REG_OFFSET_Y_LSB       0x22
#define COMPASS6_REG_OFFSET_Y_MSB       0x23
#define COMPASS6_REG_OFFSET_Z_LSB       0x24
#define COMPASS6_REG_OFFSET_Z_MSB       0x25
#define COMPASS6_REG_THR_L              0x26
#define COMPASS6_REG_THR_H              0x27
#define COMPASS6_REG_TEMPERATURE_VAL    0x31

/*! @} */ // compass6_reg

/**
 * @defgroup compass6_set Compass 6 Registers Settings
 * @brief Settings for registers of Compass 6 Click driver.
 */

/**
 * @addtogroup compass6_set
 * @{
 */

/**
 * @brief Compass 6 identification value.
 * @details Specified identification of Compass 6 Click driver.
 */
#define COMPASS6_WHO_AM_I               0x49
#define COMPASS6_VERSION                0x11
#define COMPASS6_ALPS                   0x15

/**
 * @brief Compass 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Compass 6 Click driver.
 */
#define COMPASS6_SET_DEV_ADDR           0x0C

/*! @} */ // compass6_set

/**
 * @defgroup compass6_map Compass 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Compass 6 Click driver.
 */

/**
 * @addtogroup compass6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Compass 6 Click to the selected MikroBUS.
 */
#define COMPASS6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // compass6_map
/*! @} */ // compass6

/**
 * @brief Compass 6 Click context object.
 * @details Context object definition of Compass 6 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  rdy;      /**< Data ready. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} compass6_t;

/**
 * @brief Compass 6 Click configuration object.
 * @details Configuration object definition of Compass 6 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rdy;        /**< Data ready. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} compass6_cfg_t;

/**
 * @brief Compass 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   COMPASS6_OK = 0,
   COMPASS6_ERROR = -1

} compass6_return_value_t;

/**
 * @brief Compass 6 Click axes data.
 * @details Axes data object definition of Compass 6 Click driver.
 */
typedef struct
{
   int16_t x; /**< X axis. */
   int16_t y; /**< Y axis. */
   int16_t z; /**< Z axis. */

} compass6_axes_t;

/*!
 * @addtogroup compass6 Compass 6 Click Driver
 * @brief API for configuring and manipulating Compass 6 Click driver.
 * @{
 */

/**
 * @brief Compass 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #compass6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void compass6_cfg_setup ( compass6_cfg_t *cfg );

/**
 * @brief Compass 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #compass6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #compass6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass6_init ( compass6_t *ctx, compass6_cfg_t *cfg );

/**
 * @brief Compass 6 default configuration function.
 * @details This function executes a default configuration of Compass 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #compass6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t compass6_default_cfg ( compass6_t *ctx );

/**
 * @brief Compass 6 I2C writing function.
 * @details This function writes a byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #compass6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t compass6_generic_write ( compass6_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Compass 6 I2C reading function.
 * @details This function reads a byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #compass6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t compass6_generic_read ( compass6_t *ctx, uint8_t reg, uint8_t *rx_data );

/**
 * @brief Get data ready pin state.
 * @details This function reads logic state of data ready(interrupt) pin.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @return State of data ready.
 */
uint8_t compass6_data_ready ( compass6_t *ctx );

/**
 * @brief Magnetic axes data reading.
 * @details This function reads a magnetic axes data.
 * @param[in] ctx : Click context object.
 * See #compass6_t object definition for detailed explanation.
 * @param[out] axes : Axes data object.
 * See #compass6_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t compass6_get_axes_data ( compass6_t *ctx, compass6_axes_t *axes_data );

#ifdef __cplusplus
}
#endif
#endif // COMPASS6_H

/*! @} */ // compass6

// ------------------------------------------------------------------------ END
