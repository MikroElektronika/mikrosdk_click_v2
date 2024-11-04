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
 * @file magneto10.h
 * @brief This file contains API for Magneto 10 Click Driver.
 */

#ifndef MAGNETO10_H
#define MAGNETO10_H

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
 * @addtogroup magneto10 Magneto 10 Click Driver
 * @brief API for configuring and manipulating Magneto 10 Click driver.
 * @{
 */

/**
 * @defgroup magneto10_reg Magneto 10 Registers List
 * @brief List of registers of Magneto 10 Click driver.
 */

/**
 * @addtogroup magneto10_reg
 * @{
 */

/**
 * @brief Magneto 10 register map.
 * @details Specified register map of Magneto 10 Click driver.
 */
#define MAGNETO10_REG_STAT1             0x00
#define MAGNETO10_REG_X_LSB             0x01
#define MAGNETO10_REG_X_MSB             0x02
#define MAGNETO10_REG_Y_LSB             0x03
#define MAGNETO10_REG_Y_MSB             0x04
#define MAGNETO10_REG_Z_LSB             0x05
#define MAGNETO10_REG_Z_MSB             0x06
#define MAGNETO10_REG_STAT2             0x07
#define MAGNETO10_REG_T_LSB             0x08
#define MAGNETO10_REG_T_MSB             0x09
#define MAGNETO10_REG_CID               0x0A
#define MAGNETO10_REG_DID               0x0B
#define MAGNETO10_REG_CTRL              0x10
#define MAGNETO10_REG_RST               0x11
#define MAGNETO10_REG_OSR_DIG_FILT      0x14
#define MAGNETO10_REG_T_EN_DIG_FILT_Z   0x15

/*! @} */ // magneto10_reg

/**
 * @defgroup magneto10_set Magneto 10 Registers Settings
 * @brief Settings for registers of Magneto 10 Click driver.
 */

/**
 * @addtogroup magneto10_set
 * @{
 */

/**
 * @brief Magneto 10 operating mode values.
 * @details Specified values for operating modes of Magneto 10 Click driver.
 */
#define MAGNETO10_MODE_IDLE             0x00
#define MAGNETO10_MODE_SINGLE_MEAS      0x01
#define MAGNETO10_MODE_CONT_MEAS_10HZ   0x02
#define MAGNETO10_MODE_CONT_MEAS_20HZ   0x03
#define MAGNETO10_MODE_CONT_MEAS_50HZ   0x04
#define MAGNETO10_MODE_CONT_MEAS_100HZ  0x05
#define MAGNETO10_MODE_SELF_TEST        0x06
#define MAGNETO10_MODE_CONT_MEAS_200HZ  0x0A
#define MAGNETO10_MODE_CONT_MEAS_500HZ  0x0B
#define MAGNETO10_MODE_CONT_MEAS_800HZ  0x0C
#define MAGNETO10_MODE_CONT_MEAS_1400HZ 0x0D
#define MAGNETO10_MODE_POWER_DOWN       0x0F

/**
 * @brief Magneto 10 identification values.
 * @details Specified identification values of Magneto 10 Click driver.
 */
#define MAGNETO10_COMPANY_ID            0x98
#define MAGNETO10_DEVICE_ID             0xBA

/**
 * @brief Magneto 10 reset value.
 * @details Specified reset value of Magneto 10 Click driver.
 */
#define MAGNETO10_RESET                 0x06

/**
 * @brief Magneto 10 status values.
 * @details Specified status values of Magneto 10 Click driver.
 */
#define MAGNETO10_STAT1_RT              0x08
#define MAGNETO10_STAT1_DRDY            0x01
#define MAGNETO10_STAT2_DOR             0x02
#define MAGNETO10_STAT2_HOVF            0x01

/**
 * @brief Magneto 10 temperature sensor macros.
 * @details Specified macros for temperature sensor of Magneto 10 Click driver.
 */
#define MAGNETO10_TEMPERATURE_RES       50.0
#define MAGNETO10_TEMPERATURE_ENABLE    0x01
#define MAGNETO10_TEMPERATURE_DISABLE   0x00
#define MAGNETO10_TEMPERATURE_EN_MASK   0x20

/**
 * @brief Magneto 10 magnetic flux resolution.
 * @details Specified resolution for magnetic flux of Magneto 10 Click driver.
 */
#define MAGNETO10_MAG_FLUX_RESOLUTION   0.15 

/**
 * @brief Magneto 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Magneto 10 Click driver.
 */
#define MAGNETO10_SET_DEV_ADDR          0x0C

/*! @} */ // magneto10_set

/**
 * @defgroup magneto10_map Magneto 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Magneto 10 Click driver.
 */

/**
 * @addtogroup magneto10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magneto 10 Click to the selected MikroBUS.
 */
#define MAGNETO10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // magneto10_map
/*! @} */ // magneto10

/**
 * @brief Magneto 10 Click context object.
 * @details Context object definition of Magneto 10 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} magneto10_t;

/**
 * @brief Magneto 10 Click configuration object.
 * @details Configuration object definition of Magneto 10 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} magneto10_cfg_t;

/**
 * @brief Magneto 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETO10_OK = 0,
    MAGNETO10_ERROR = -1

} magneto10_return_value_t;

/*!
 * @addtogroup magneto10 Magneto 10 Click Driver
 * @brief API for configuring and manipulating Magneto 10 Click driver.
 * @{
 */

/**
 * @brief Magneto 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneto10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneto10_cfg_setup ( magneto10_cfg_t *cfg );

/**
 * @brief Magneto 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneto10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_init ( magneto10_t *ctx, magneto10_cfg_t *cfg );

/**
 * @brief Magneto 10 default configuration function.
 * @details This function executes a default configuration of Magneto 10
 * Click board.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magneto10_default_cfg ( magneto10_t *ctx );

/**
 * @brief Magneto 10 mem write single function.
 * @details This function writes a single data byte to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_mem_write_single ( magneto10_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Magneto 10 mem write multiple function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_mem_write_multiple ( magneto10_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Magneto 10 mem direct read function.
 * @details This function reads a desired number of data bytes starting from
 * the register at address 0x00 by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_mem_direct_read ( magneto10_t *ctx, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Magneto 10 mem read function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_mem_read ( magneto10_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Magneto 10 check communication function.
 * @details This function checks the communication by reading and verifying the company and device
 * identification registers.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_check_communication ( magneto10_t *ctx );

/**
 * @brief Magneto 10 check data ready function.
 * @details This function checks if the data is ready.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @return @li @c  1 - Data is ready,
 *         @li @c  0 - Data is not ready,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_check_data_ready ( magneto10_t *ctx );

/**
 * @brief Magneto 10 get magnetic flux function.
 * @details This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux
 * data in microTesla.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[out] x_axis : X-axis data in microTesla.
 * @param[out] y_axis : Y-axis data in microTesla.
 * @param[out] z_axis : Z-axis data in microTesla.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_get_magnetic_flux ( magneto10_t *ctx, float *x_axis, float *y_axis, float *z_axis );

/**
 * @brief Magneto 10 get temperature function.
 * @details This function reads the raw temperature value and converts it to Celsius.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[out] temperature : Internal temperature data in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_get_temperature ( magneto10_t *ctx, float *temperature );

/**
 * @brief Magneto 10 reset function.
 * @details This function resets the device to factory settings.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_reset ( magneto10_t *ctx );

/**
 * @brief Magneto 10 set operating mode function.
 * @details This function sets the device operating mode.
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[in] mode : Operating mode.
 * See Magneto 10 operating mode values macros definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_set_operating_mode ( magneto10_t *ctx, uint8_t mode );

/**
 * @brief Magneto 10 enable temperature sensor function.
 * @details This function enables or disables the internal temperature sensor
 * @param[in] ctx : Click context object.
 * See #magneto10_t object definition for detailed explanation.
 * @param[in] enable : @li @c  1 - Enable,
 *                     @li @c  0 - Disable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto10_enable_temperature_sensor ( magneto10_t *ctx, uint8_t enable );

#ifdef __cplusplus
}
#endif
#endif // MAGNETO10_H

/*! @} */ // magneto10

// ------------------------------------------------------------------------ END
