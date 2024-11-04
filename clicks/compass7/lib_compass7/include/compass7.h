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
 * @file compass7.h
 * @brief This file contains API for Compass 7 Click Driver.
 */

#ifndef COMPASS7_H
#define COMPASS7_H

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
 * @addtogroup compass7 Compass 7 Click Driver
 * @brief API for configuring and manipulating Compass 7 Click driver.
 * @{
 */

/**
 * @defgroup compass7_reg Compass 7 Registers List
 * @brief List of registers of Compass 7 Click driver.
 */

/**
 * @addtogroup compass7_reg
 * @{
 */

/**
 * @brief Compass 7 register map.
 * @details Specified register map of Compass 7 Click driver.
 */
#define COMPASS7_REG_XOUT0                  0x00
#define COMPASS7_REG_XOUT1                  0x01
#define COMPASS7_REG_YOUT0                  0x02
#define COMPASS7_REG_YOUT1                  0x03
#define COMPASS7_REG_ZOUT0                  0x04
#define COMPASS7_REG_ZOUT1                  0x05
#define COMPASS7_REG_XOUT2                  0x06
#define COMPASS7_REG_YOUT2                  0x07
#define COMPASS7_REG_ZOUT2                  0x08
#define COMPASS7_REG_TOUT                   0x09
#define COMPASS7_REG_TPH0                   0x0A
#define COMPASS7_REG_TPH1                   0x0B
#define COMPASS7_REG_TU                     0x0C
#define COMPASS7_REG_STATUS1                0x18
#define COMPASS7_REG_STATUS0                0x19
#define COMPASS7_REG_ODR                    0x1A
#define COMPASS7_REG_CONTROL0               0x1B
#define COMPASS7_REG_CONTROL1               0x1C
#define COMPASS7_REG_CONTROL2               0x1D
#define COMPASS7_REG_ST_X_TH                0x1E
#define COMPASS7_REG_ST_Y_TH                0x1F
#define COMPASS7_REG_ST_Z_TH                0x20
#define COMPASS7_REG_ST_X                   0x27
#define COMPASS7_REG_ST_Y                   0x28
#define COMPASS7_REG_ST_Z                   0x29
#define COMPASS7_REG_PRODUCT_ID             0x39

/*! @} */ // compass7_reg

/**
 * @defgroup compass7_set Compass 7 Registers Settings
 * @brief Settings for registers of Compass 7 Click driver.
 */

/**
 * @addtogroup compass7_set
 * @{
 */

/**
 * @brief Compass 7 status 1 register settings.
 * @details Specified status 1 register settings of Compass 7 Click driver.
 */
#define COMPASS7_STATUS1_MEAS_T_DONE        0x80
#define COMPASS7_STATUS1_MEAS_M_DONE        0x40
#define COMPASS7_STATUS1_SAT_SENSOR         0x20
#define COMPASS7_STATUS1_OTP_READ_DONE      0x10
#define COMPASS7_STATUS1_ST_FAIL            0x08
#define COMPASS7_STATUS1_MDT_FLAG_INT       0x04
#define COMPASS7_STATUS1_MEAS_T_DONE_INT    0x02
#define COMPASS7_STATUS1_MEAS_M_DONE_INT    0x01

/**
 * @brief Compass 7 internal control 0 register settings.
 * @details Specified internal control 0 register settings of Compass 7 Click driver.
 */
#define COMPASS7_CONTROL0_CMM_FREQ_EN       0x80
#define COMPASS7_CONTROL0_AUTO_ST_EN        0x40
#define COMPASS7_CONTROL0_AUTO_SR_EN        0x20
#define COMPASS7_CONTROL0_DO_RESET          0x10
#define COMPASS7_CONTROL0_DO_SET            0x08
#define COMPASS7_CONTROL0_START_MDT         0x04
#define COMPASS7_CONTROL0_TAKE_MEAS_T       0x02
#define COMPASS7_CONTROL0_TAKE_MEAS_M       0x01

/**
 * @brief Compass 7 internal control 1 register settings.
 * @details Specified internal control 1 register settings of Compass 7 Click driver.
 */
#define COMPASS7_CONTROL1_SW_RESET          0x80
#define COMPASS7_CONTROL1_ST_ENM            0x40
#define COMPASS7_CONTROL1_ST_ENP            0x20
#define COMPASS7_CONTROL1_Z_INHIBIT         0x10
#define COMPASS7_CONTROL1_Y_INHIBIT         0x08
#define COMPASS7_CONTROL1_X_INHIBIT         0x04
#define COMPASS7_CONTROL1_BW_6p6MS          0x00
#define COMPASS7_CONTROL1_BW_3p5MS          0x01
#define COMPASS7_CONTROL1_BW_2p0MS          0x02
#define COMPASS7_CONTROL1_BW_1p2MS          0x03
#define COMPASS7_CONTROL1_BW_BIT_MASK       0x03

/**
 * @brief Compass 7 internal control 2 register settings.
 * @details Specified internal control 2 register settings of Compass 7 Click driver.
 */
#define COMPASS7_CONTROL2_HPOWER            0x80
#define COMPASS7_CONTROL2_INT_MEAS_DONE_EN  0x40
#define COMPASS7_CONTROL2_INT_MDT_EN        0x20
#define COMPASS7_CONTROL2_CMM_EN            0x10
#define COMPASS7_CONTROL2_EN_PRD_SET        0x08
#define COMPASS7_CONTROL2_PRD_SET_1_SMPL    0x00
#define COMPASS7_CONTROL2_PRD_SET_25_SMPL   0x01
#define COMPASS7_CONTROL2_PRD_SET_75_SMPL   0x02
#define COMPASS7_CONTROL2_PRD_SET_100_SMPL  0x03
#define COMPASS7_CONTROL2_PRD_SET_250_SMPL  0x04
#define COMPASS7_CONTROL2_PRD_SET_500_SMPL  0x05
#define COMPASS7_CONTROL2_PRD_SET_1000_SMPL 0x06
#define COMPASS7_CONTROL2_PRD_SET_2000_SMPL 0x07
#define COMPASS7_CONTROL2_PRD_SET_BIT_MASK  0x07

/**
 * @brief Compass 7 ODR register settings.
 * @details Specified ODR register settings of Compass 7 Click driver.
 */
#define COMPASS7_ODR_DISABLE                0
#define COMPASS7_ODR_1HZ                    1
#define COMPASS7_ODR_2HZ                    2
#define COMPASS7_ODR_5HZ                    5
#define COMPASS7_ODR_10HZ                   10
#define COMPASS7_ODR_25HZ                   25
#define COMPASS7_ODR_50HZ                   50
#define COMPASS7_ODR_100HZ                  100

/**
 * @brief Compass 7 data calculation values.
 * @details Specified data calculation values of Compass 7 Click driver.
 */
#define COMPASS7_MAGNETIC_OFFSET            0x080000l
#define COMPASS7_MAGNETIC_RESOLUTION        0.0625
#define COMPASS7_MILLIGAUSS_TO_GAUSS        0.001
#define COMPASS7_TEMPERATURE_OFFSET         75
#define COMPASS7_TEMPERATURE_RESOLUTION     0.8
#define COMPASS7_TIMEOUT                    2000

/**
 * @brief Compass 7 measurement mode settings.
 * @details Specified measurement mode settings of Compass 7 Click driver.
 */
#define COMPASS7_MEAS_SINGLE_T              0
#define COMPASS7_MEAS_SINGLE_M              1
#define COMPASS7_MEAS_CONTINUOUS_M_1HZ      2
#define COMPASS7_MEAS_CONTINUOUS_M_2HZ      3
#define COMPASS7_MEAS_CONTINUOUS_M_5HZ      4
#define COMPASS7_MEAS_CONTINUOUS_M_10HZ     5
#define COMPASS7_MEAS_CONTINUOUS_M_25HZ     6
#define COMPASS7_MEAS_CONTINUOUS_M_50HZ     7
#define COMPASS7_MEAS_CONTINUOUS_M_100HZ    8

/**
 * @brief Compass 7 product ID value.
 * @details Specified product ID value of Compass 7 Click driver.
 */
#define COMPASS7_PRODUCT_ID                 0x10

/**
 * @brief Compass 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Compass 7 Click driver.
 */
#define COMPASS7_DEVICE_ADDRESS             0x30

/*! @} */ // compass7_set

/**
 * @defgroup compass7_map Compass 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Compass 7 Click driver.
 */

/**
 * @addtogroup compass7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Compass 7 Click to the selected MikroBUS.
 */
#define COMPASS7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // compass7_map
/*! @} */ // compass7

/**
 * @brief Compass 7 Click context object.
 * @details Context object definition of Compass 7 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} compass7_t;

/**
 * @brief Compass 7 Click configuration object.
 * @details Configuration object definition of Compass 7 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} compass7_cfg_t;

/**
 * @brief Compass 7 magnetic flux data object.
 * @details Magnetic flux data object definition of Compass 7 Click driver.
 */
typedef struct
{
    float x_axis;
    float y_axis;
    float z_axis;

} compass7_magnetic_flux_t;

/**
 * @brief Compass 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COMPASS7_OK = 0,
    COMPASS7_ERROR = -1

} compass7_return_value_t;

/*!
 * @addtogroup compass7 Compass 7 Click Driver
 * @brief API for configuring and manipulating Compass 7 Click driver.
 * @{
 */

/**
 * @brief Compass 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #compass7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void compass7_cfg_setup ( compass7_cfg_t *cfg );

/**
 * @brief Compass 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #compass7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_init ( compass7_t *ctx, compass7_cfg_t *cfg );

/**
 * @brief Compass 7 default configuration function.
 * @details This function executes a default configuration of Compass 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t compass7_default_cfg ( compass7_t *ctx );

/**
 * @brief Compass 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_generic_write ( compass7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Compass 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_generic_read ( compass7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Compass 7 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_write_register ( compass7_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Compass 7 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_read_register ( compass7_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Compass 7 check communication function.
 * @details This function checks the communication by reading and verifying the product ID.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_check_communication ( compass7_t *ctx );

/**
 * @brief Compass 7 soft reset function.
 * @details This function performs the software reset by setting a desired bit in the Control 1 register.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note At least 20ms delay for the power-on time is required after reset.
 */
err_t compass7_soft_reset ( compass7_t *ctx );

/**
 * @brief Compass 7 set measurement mode function.
 * @details This function sets the control and ODR registers for the selected measurement mode.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @param[in] mode : Measurement mode: @li @c 0 - Single temperature,
 *                                     @li @c 1 - Single magnetic,
 *                                     @li @c 2 - Continuous magnetic at 1 Hz ODR,
 *                                     @li @c 3 - Continuous magnetic at 2 Hz ODR,
 *                                     @li @c 4 - Continuous magnetic at 5 Hz ODR,
 *                                     @li @c 5 - Continuous magnetic at 10 Hz ODR,
 *                                     @li @c 6 - Continuous magnetic at 25 Hz ODR,
 *                                     @li @c 7 - Continuous magnetic at 50 Hz ODR,
 *                                     @li @c 8 - Continuous magnetic at 100 Hz ODR,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_set_measurement_mode ( compass7_t *ctx, uint8_t mode );

/**
 * @brief Compass 7 get magnetic flux function.
 * @details This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux
 * data in Gauss.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @param[out] compass7_magnetic_flux_t : Flux data of X, Y, and Z axis in Gauss.
 * See #compass7_magnetic_flux_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_get_magnetic_flux ( compass7_t *ctx, compass7_magnetic_flux_t *flux );

/**
 * @brief Compass 7 get temperature function.
 * @details This function reads the temperature measurements in Celsius.
 * @param[in] ctx : Click context object.
 * See #compass7_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass7_get_temperature ( compass7_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // COMPASS7_H

/*! @} */ // compass7

// ------------------------------------------------------------------------ END
