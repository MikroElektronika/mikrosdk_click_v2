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
 * @file magneto6.h
 * @brief This file contains API for Magneto 6 Click Driver.
 */

#ifndef MAGNETO6_H
#define MAGNETO6_H

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
 * @addtogroup magneto6 Magneto 6 Click Driver
 * @brief API for configuring and manipulating Magneto 6 Click driver.
 * @{
 */

/**
 * @defgroup magneto6_reg Magneto 6 Registers List
 * @brief List of registers of Magneto 6 Click driver.
 */

/**
 * @addtogroup magneto6_reg
 * @{
 */

/**
 * @brief Magneto 6 register list.
 * @details Specified register list of Magneto 6 Click driver.
 */
#define MAGNETO6_REG_MAGNETIC_X_MSB         0x00
#define MAGNETO6_REG_MAGNETIC_Y_MSB         0x01
#define MAGNETO6_REG_MAGNETIC_Z_MSB         0x02
#define MAGNETO6_REG_TEMPERATURE_MSB        0x03
#define MAGNETO6_REG_MAGNETIC_XY_LSB        0x04
#define MAGNETO6_REG_TEMPERATURE_Z_LSB      0x05
#define MAGNETO6_REG_DIAG                   0x06
#define MAGNETO6_REG_CONFIG                 0x10
#define MAGNETO6_REG_MOD1                   0x11
#define MAGNETO6_REG_MOD2                   0x13
#define MAGNETO6_REG_VERSION                0x16

/*! @} */ // magneto6_reg

/**
 * @defgroup magneto6_set Magneto 6 Registers Settings
 * @brief Settings for registers of Magneto 6 Click driver.
 */

/**
 * @addtogroup magneto6_set
 * @{
 */

/**
 * @brief Magneto 6 CONFIG register setting.
 * @details Specified setting for CONFIG register of Magneto 6 Click driver.
 */
#define MAGNETO6_CONFIG_DISABLE_TEMP        0x80
#define MAGNETO6_CONFIG_ENABLE_ANGULAR_XY   0x40
#define MAGNETO6_CONFIG_TRIGGER_DISABLE     0x00
#define MAGNETO6_CONFIG_TRIGGER_MSB         0x10
#define MAGNETO6_CONFIG_TRIGGER_REG_READ    0x20
#define MAGNETO6_CONFIG_TRIGGER_MASK        0x30
#define MAGNETO6_CONFIG_SHORT_RANGE_SENS_EN 0x08
#define MAGNETO6_CONFIG_TL_COMP_TC0         0x00
#define MAGNETO6_CONFIG_TL_COMP_TC1         0x02
#define MAGNETO6_CONFIG_TL_COMP_TC2         0x04
#define MAGNETO6_CONFIG_TL_COMP_TC3         0x06
#define MAGNETO6_CONFIG_TL_COMP_MASK        0x06
#define MAGNETO6_CONFIG_PARITY_BIT          0x01

/**
 * @brief Magneto 6 MOD1 register setting.
 * @details Specified setting for MOD1 register of Magneto 6 Click driver.
 */
#define MAGNETO6_MOD1_FUSE_PARITY           0x80
#define MAGNETO6_MOD1_I2C_ADDR_0            0x00
#define MAGNETO6_MOD1_I2C_ADDR_1            0x20
#define MAGNETO6_MOD1_I2C_ADDR_2            0x40
#define MAGNETO6_MOD1_I2C_ADDR_3            0x60
#define MAGNETO6_MOD1_I2C_ADDR_MASK         0x60
#define MAGNETO6_MOD1_1BYTE_READ_EN         0x10
#define MAGNETO6_MOD1_COLLISION_AVOID       0x08
#define MAGNETO6_MOD1_INT_DISABLE           0x04
#define MAGNETO6_MOD1_MODE_LOW_POWER        0x00
#define MAGNETO6_MOD1_MODE_MASTER           0x01
#define MAGNETO6_MOD1_MODE_FAST             0x03
#define MAGNETO6_MOD1_MODE_MASK             0x03

/**
 * @brief Magneto 6 MOD2 register setting.
 * @details Specified setting for MOD2 register of Magneto 6 Click driver.
 */
#define MAGNETO6_MOD2_FUPDATE_SLOW          0x80
#define MAGNETO6_MOD2_FACTORY_MASK          0x7F

/**
 * @brief Magneto 6 DIAG register setting.
 * @details Specified setting for DIAG register of Magneto 6 Click driver.
 */
#define MAGNETO6_DIAG_BUS_PARITY            0x80
#define MAGNETO6_DIAG_FUSE_PARITY           0x40
#define MAGNETO6_DIAG_CFG_PARITY            0x20
#define MAGNETO6_DIAG_T_BIT                 0x10
#define MAGNETO6_DIAG_PD3_FLAG              0x08
#define MAGNETO6_DIAG_PD0_FLAG              0x04
#define MAGNETO6_DIAG_FRAME_COUNTER_MASK    0x03

/**
 * @brief Magneto 6 VERSION register setting.
 * @details Specified setting for VERSION register of Magneto 6 Click driver.
 */
#define MAGNETO6_VERSION_FACTORY_MASK       0xC0
#define MAGNETO6_VERSION_TYPE_MASK          0x30
#define MAGNETO6_VERSION_HWV_MASK           0x0F

/**
 * @brief Magneto 6 measurement setting.
 * @details Specified setting for measurement of Magneto 6 Click driver.
 */
#define MAGNETO6_TEMP_25_DIGIT              1180
#define MAGNETO6_TEMP_25                    25
#define MAGNETO6_TEMP_RES                   0.24f
#define MAGNETO6_MAGNETIC_RES_MILLI_T       0.13f

/**
 * @brief Magneto 6 I2C timeout setting.
 * @details Specified setting for I2C timeout of Magneto 6 Click driver.
 */
#define MAGNETO6_I2C_TIMEOUT                100000ul

/**
 * @brief Magneto 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Magneto 6 Click driver.
 */
#define MAGNETO6_DEVICE_ADDRESS_0           0x35
#define MAGNETO6_DEVICE_ADDRESS_1           0x22
#define MAGNETO6_DEVICE_ADDRESS_2           0x78
#define MAGNETO6_DEVICE_ADDRESS_3           0x44

/*! @} */ // magneto6_set

/**
 * @defgroup magneto6_map Magneto 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Magneto 6 Click driver.
 */

/**
 * @addtogroup magneto6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magneto 6 Click to the selected MikroBUS.
 */
#define MAGNETO6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ien = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // magneto6_map
/*! @} */ // magneto6

/**
 * @brief Magneto 6 Click data object.
 * @details Data object definition of Magneto 6 Click driver.
 */
typedef struct
{
    float x_data;               /**< X-axis data. */
    float y_data;               /**< Y-axis data. */
    float z_data;               /**< Z-axis data. */
    float temperature;          /**< Temperature in degrees Celsius. */

} magneto6_data_t;

/**
 * @brief Magneto 6 Click context object.
 * @details Context object definition of Magneto 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ien;          /**< Interrupt enable pin (Active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    
    uint8_t i2c_started;        /**< I2C started flag. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} magneto6_t;

/**
 * @brief Magneto 6 Click configuration object.
 * @details Configuration object definition of Magneto 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ien;             /**< Interrupt enable pin (Active high). */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint8_t    i2c_address;     /**< I2C slave address. */

} magneto6_cfg_t;

/**
 * @brief Magneto 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETO6_OK = 0,
    MAGNETO6_ERROR = -1

} magneto6_return_value_t;

/*!
 * @addtogroup magneto6 Magneto 6 Click Driver
 * @brief API for configuring and manipulating Magneto 6 Click driver.
 * @{
 */

/**
 * @brief Magneto 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneto6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneto6_cfg_setup ( magneto6_cfg_t *cfg );

/**
 * @brief Magneto 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneto6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto6_init ( magneto6_t *ctx, magneto6_cfg_t *cfg );

/**
 * @brief Magneto 6 default configuration function.
 * @details This function executes a default configuration of Magneto 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magneto6_default_cfg ( magneto6_t *ctx );

/**
 * @brief Magneto 6 write reg function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto6_write_reg ( magneto6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Magneto 6 read reg function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto6_read_reg ( magneto6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Magneto 6 set ien pin function.
 * @details This function sets the IEN pin logic state.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void magneto6_set_ien_pin ( magneto6_t *ctx, uint8_t state );

/**
 * @brief Magneto 6 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t magneto6_get_int_pin ( magneto6_t *ctx );

/**
 * @brief Magneto 6 read data function.
 * @details This function reads the measurements of the 3-axes magnetic field sensor in mT and
 * the temperature sensor in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * See #magneto6_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto6_read_data ( magneto6_t *ctx, magneto6_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // MAGNETO6_H

/*! @} */ // magneto6

// ------------------------------------------------------------------------ END
