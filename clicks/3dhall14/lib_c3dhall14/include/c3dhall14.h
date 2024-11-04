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
 * @file c3dhall14.h
 * @brief This file contains API for 3D Hall 14 Click Driver.
 */

#ifndef C3DHALL14_H
#define C3DHALL14_H

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
 * @addtogroup c3dhall14 3D Hall 14 Click Driver
 * @brief API for configuring and manipulating 3D Hall 14 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall14_reg 3D Hall 14 Registers List
 * @brief List of registers of 3D Hall 14 Click driver.
 */

/**
 * @addtogroup c3dhall14_reg
 * @{
 */

/**
 * @brief 3D Hall 14 register map.
 * @details Specified register map of 3D Hall 14 Click driver.
 */
#define C3DHALL14_REG_STAT1                     0x00
#define C3DHALL14_REG_X_LSB                     0x01
#define C3DHALL14_REG_X_MSB                     0x02
#define C3DHALL14_REG_Y_LSB                     0x03
#define C3DHALL14_REG_Y_MSB                     0x04
#define C3DHALL14_REG_Z_LSB                     0x05
#define C3DHALL14_REG_Z_MSB                     0x06
#define C3DHALL14_REG_STAT2                     0x07
#define C3DHALL14_REG_T_LSB                     0x08
#define C3DHALL14_REG_T_MSB                     0x09
#define C3DHALL14_REG_CID                       0x0A
#define C3DHALL14_REG_DID                       0x0B
#define C3DHALL14_REG_CTRL1                     0x0E
#define C3DHALL14_REG_CTRL2                     0x0F
#define C3DHALL14_REG_RST                       0x11
#define C3DHALL14_REG_CTRL3                     0x14
#define C3DHALL14_REG_CTRL4                     0x15
#define C3DHALL14_REG_X_THR_LSB                 0x58
#define C3DHALL14_REG_X_THR_MSB                 0x59
#define C3DHALL14_REG_Y_THR_LSB                 0x5A
#define C3DHALL14_REG_Y_THR_MSB                 0x5B
#define C3DHALL14_REG_Z_THR_LSB                 0x5C
#define C3DHALL14_REG_Z_THR_MSB                 0x5D

/*! @} */ // c3dhall14_reg

/**
 * @defgroup c3dhall14_set 3D Hall 14 Registers Settings
 * @brief Settings for registers of 3D Hall 14 Click driver.
 */

/**
 * @addtogroup c3dhall14_set
 * @{
 */

/**
 * @brief 3D Hall 14 operating mode values.
 * @details Specified values for operating modes of 3D Hall 14 Click driver.
 */
#define C3DHALL14_MODE_POWER_DOWN_0             0x00
#define C3DHALL14_MODE_SINGLE_MEAS_0            0x01
#define C3DHALL14_MODE_CONT_MEAS_5HZ            0x02
#define C3DHALL14_MODE_CONT_MEAS_10HZ           0x03
#define C3DHALL14_MODE_CONT_MEAS_20HZ           0x04
#define C3DHALL14_MODE_CONT_MEAS_50HZ           0x05
#define C3DHALL14_MODE_CONT_MEAS_100HZ          0x06
#define C3DHALL14_MODE_SELF_TEST                0x07
#define C3DHALL14_MODE_POWER_DOWN_1             0x08
#define C3DHALL14_MODE_SINGLE_MEAS_1            0x09
#define C3DHALL14_MODE_CONT_MEAS_200HZ          0x0A
#define C3DHALL14_MODE_CONT_MEAS_500HZ          0x0B
#define C3DHALL14_MODE_CONT_MEAS_700HZ          0x0C
#define C3DHALL14_MODE_CONT_MEAS_1000HZ         0x0D
#define C3DHALL14_MODE_CONT_MEAS_1400HZ         0x0E
#define C3DHALL14_MODE_POWER_DOWN_2             0x0F
#define C3DHALL14_MODE_MASK                     0x0F

/**
 * @brief 3D Hall 14 identification values.
 * @details Specified identification values of 3D Hall 14 Click driver.
 */
#define C3DHALL14_COMPANY_ID                    0x94
#define C3DHALL14_DEVICE_ID                     0xAA

/**
 * @brief 3D Hall 14 reset value.
 * @details Specified reset value of 3D Hall 14 Click driver.
 */
#define C3DHALL14_RESET                         0x06

/**
 * @brief 3D Hall 14 status values.
 * @details Specified status values of 3D Hall 14 Click driver.
 */
#define C3DHALL14_STAT1_INT                     0x10
#define C3DHALL14_STAT1_RT                      0x08
#define C3DHALL14_STAT1_DRDY                    0x01
#define C3DHALL14_STAT2_DOR                     0x08
#define C3DHALL14_STAT2_HOVF_Z                  0x04
#define C3DHALL14_STAT2_HOVF_Y                  0x02
#define C3DHALL14_STAT2_HOVF_X                  0x01

/**
 * @brief 3D Hall 14 data ready interrupt enable macros.
 * @details Specified macros for data ready interrupt enable of 3D Hall 14 Click driver.
 */
#define C3DHALL14_DRDY_INT_ENABLE               0x01
#define C3DHALL14_DRDY_INT_DISABLE              0x00
#define C3DHALL14_DRDY_INT_EN_MASK              0x08

/**
 * @brief 3D Hall 14 temperature sensor macros.
 * @details Specified macros for temperature sensor of 3D Hall 14 Click driver.
 */
#define C3DHALL14_TEMPERATURE_RES               50.0f
#define C3DHALL14_TEMPERATURE_ENABLE            0x01
#define C3DHALL14_TEMPERATURE_DISABLE           0x00
#define C3DHALL14_TEMPERATURE_EN_MASK           0x20

/**
 * @brief 3D Hall 14 magnetic flux resolution.
 * @details Specified resolution for magnetic flux of 3D Hall 14 Click driver.
 */
#define C3DHALL14_MAG_FLUX_RES_H                1.5f
#define C3DHALL14_MAG_FLUX_RES_L                0.15f
#define C3DHALL14_RANGE_HIGH_LOW_CURRENT        0x00
#define C3DHALL14_RANGE_HIGH_LOW_NOISE          0x01
#define C3DHALL14_RANGE_LOW_LOW_NOISE           0x02
#define C3DHALL14_RANGE_MASK                    0xE0
#define C3DHALL14_RANGE_SHIFT                   5

/**
 * @brief 3D Hall 14 device address setting.
 * @details Specified setting for device slave address selection of
 * 3D Hall 14 Click driver.
 */
#define C3DHALL14_DEVICE_ADDRESS                0x60

/*! @} */ // c3dhall14_set

/**
 * @defgroup c3dhall14_map 3D Hall 14 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 14 Click driver.
 */

/**
 * @addtogroup c3dhall14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 14 Click to the selected MikroBUS.
 */
#define C3DHALL14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3dhall14_map
/*! @} */ // c3dhall14

/**
 * @brief 3D Hall 14 Click context object.
 * @details Context object definition of 3D Hall 14 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float mag_flux_res;         /**< Magnetic flux resolution. */
    uint8_t drdy_int_out;       /**< Data ready interrupt output enable flag. */

} c3dhall14_t;

/**
 * @brief 3D Hall 14 Click configuration object.
 * @details Configuration object definition of 3D Hall 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} c3dhall14_cfg_t;

/**
 * @brief 3D Hall 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL14_OK = 0,
    C3DHALL14_ERROR = -1

} c3dhall14_return_value_t;

/*!
 * @addtogroup c3dhall14 3D Hall 14 Click Driver
 * @brief API for configuring and manipulating 3D Hall 14 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall14_cfg_setup ( c3dhall14_cfg_t *cfg );

/**
 * @brief 3D Hall 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_init ( c3dhall14_t *ctx, c3dhall14_cfg_t *cfg );

/**
 * @brief 3D Hall 14 default configuration function.
 * @details This function executes a default configuration of 3D Hall 14
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall14_default_cfg ( c3dhall14_t *ctx );

/**
 * @brief 3D Hall 14 mem write single function.
 * @details This function writes a single data byte to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_mem_write_single ( c3dhall14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 3D Hall 14 mem write multi function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_mem_write_multi ( c3dhall14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 3D Hall 14 mem direct read function.
 * @details This function reads a desired number of data bytes starting from
 * the register at address 0x00 by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_mem_direct_read ( c3dhall14_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief 3D Hall 14 mem read function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_mem_read ( c3dhall14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 3D Hall 14 check communication function.
 * @details This function checks the communication by reading and verifying the company and device
 * identification registers.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_check_communication ( c3dhall14_t *ctx );

/**
 * @brief 3D Hall 14 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3dhall14_get_int_pin ( c3dhall14_t *ctx );

/**
 * @brief 3D Hall 14 check data ready function.
 * @details This function checks if the data is ready.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @return @li @c  1 - Data is ready,
 *         @li @c  0 - Data is not ready,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_check_data_ready ( c3dhall14_t *ctx );

/**
 * @brief 3D Hall 14 get magnetic flux function.
 * @details This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux
 * data in microTesla.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[out] x_axis : X-axis data in microTesla.
 * @param[out] y_axis : Y-axis data in microTesla.
 * @param[out] z_axis : Z-axis data in microTesla.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_get_magnetic_flux ( c3dhall14_t *ctx, float *x_axis, float *y_axis, float *z_axis );

/**
 * @brief 3D Hall 14 get temperature function.
 * @details This function reads the raw temperature value and converts it to Celsius.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[out] temperature : Internal temperature data in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_get_temperature ( c3dhall14_t *ctx, float *temperature );

/**
 * @brief 3D Hall 14 reset function.
 * @details This function resets the device to factory settings.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_reset ( c3dhall14_t *ctx );

/**
 * @brief 3D Hall 14 set operating mode function.
 * @details This function sets the device operating mode.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[in] mode : Operating mode.
 * See 3D Hall 14 operating mode values macros definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_set_operating_mode ( c3dhall14_t *ctx, uint8_t mode );

/**
 * @brief 3D Hall 14 set range function.
 * @details This function sets the magnetic flux measurement range.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[in] range : @li @c 0 - Low current,
 *                    @li @c 1 - Low noise,
 *                    @li @c 2 - High range.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_set_range ( c3dhall14_t *ctx, uint8_t range );

/**
 * @brief 3D Hall 14 enable temp sensor function.
 * @details This function enables or disables the internal temperature sensor.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[in] enable : @li @c  1 - Enable,
 *                     @li @c  0 - Disable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_enable_temp_sensor ( c3dhall14_t *ctx, uint8_t enable );

/**
 * @brief 3D Hall 14 enable drdy int function.
 * @details This function enables or disables the data ready interrupt output.
 * @param[in] ctx : Click context object.
 * See #c3dhall14_t object definition for detailed explanation.
 * @param[in] enable : @li @c  1 - Enable,
 *                     @li @c  0 - Disable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall14_enable_drdy_int ( c3dhall14_t *ctx, uint8_t enable );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL14_H

/*! @} */ // c3dhall14

// ------------------------------------------------------------------------ END
