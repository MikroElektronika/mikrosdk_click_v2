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
 * @file current14.h
 * @brief This file contains API for Current 14 Click Driver.
 */

#ifndef CURRENT14_H
#define CURRENT14_H

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
 * @addtogroup current14 Current 14 Click Driver
 * @brief API for configuring and manipulating Current 14 Click driver.
 * @{
 */

/**
 * @defgroup current14_reg Current 14 Registers List
 * @brief List of registers of Current 14 Click driver.
 */

/**
 * @addtogroup current14_reg
 * @{
 */

/**
 * @brief Current 14 register list.
 * @details Specified register list of Current 14 Click driver.
 */
#define CURRENT14_REG_STA1                  0x0F
#define CURRENT14_REG_DATA_LSB              0x10
#define CURRENT14_REG_DATA_MSB              0x11
#define CURRENT14_REG_CNTL1                 0x1B
#define CURRENT14_REG_CNTL2                 0x1C
#define CURRENT14_REG_CNTL3                 0x1D
#define CURRENT14_REG_CNTL4_LSB             0x5C
#define CURRENT14_REG_CNTL4_MSB             0x5D

/*! @} */ // current14_reg

/**
 * @defgroup current14_set Current 14 Registers Settings
 * @brief Settings for registers of Current 14 Click driver.
 */

/**
 * @addtogroup current14_set
 * @{
 */

/**
 * @brief Current 14 STA1 register setting.
 * @details Specified setting for STA1 register of Current 14 Click driver.
 */
#define CURRENT14_STA1_RD_DRDY              0x80

/**
 * @brief Current 14 CNTL1 register setting.
 * @details Specified setting for CNTL1 register of Current 14 Click driver.
 */
#define CURRENT14_CNTL1_PC1_POWER_DOWN      0x00
#define CURRENT14_CNTL1_PC1_ACTIVE          0x80
#define CURRENT14_CNTL1_PC1_MASK            0x80
#define CURRENT14_CNTL1_RST_LV_RELEASE      0x00
#define CURRENT14_CNTL1_RST_LV_ACTIVE       0x20
#define CURRENT14_CNTL1_RST_LV_MASK         0x20
#define CURRENT14_CNTL1_ODR_20_HZ           0x00
#define CURRENT14_CNTL1_ODR_100_HZ          0x08
#define CURRENT14_CNTL1_ODR_200_HZ          0x10
#define CURRENT14_CNTL1_ODR_1_KHZ           0x18
#define CURRENT14_CNTL1_ODR_MASK            0x18
#define CURRENT14_CNTL1_FS1_CONTINUOUS      0x00
#define CURRENT14_CNTL1_FS1_SINGLE          0x02
#define CURRENT14_CNTL1_FS1_MASK            0x02

/**
 * @brief Current 14 CNTL2 register setting.
 * @details Specified setting for CNTL2 register of Current 14 Click driver.
 */
#define CURRENT14_CNTL2_ALERT_EN            0x08

/**
 * @brief Current 14 CNTL3 register setting.
 * @details Specified setting for CNTL3 register of Current 14 Click driver.
 */
#define CURRENT14_CNTL3_FORCE               0x40

/**
 * @brief Current 14 CNTL4 register setting.
 * @details Specified setting for CNTL4 register of Current 14 Click driver.
 */
#define CURRENT14_CNTL4_RELEASE             0x0000

/**
 * @brief Current 14 ODR setting.
 * @details Specified setting for ODR of Current 14 Click driver.
 */
#define CURRENT14_ODR_20_HZ                 0
#define CURRENT14_ODR_100_HZ                1
#define CURRENT14_ODR_200_HZ                2
#define CURRENT14_ODR_1_KHZ                 3

/**
 * @brief Current 14 timeout setting.
 * @details Specified setting for timeout of Current 14 Click driver.
 */
#define CURRENT14_TIMEOUT_MS                2000

/**
 * @brief Current 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Current 14 Click driver.
 */
#define CURRENT14_DEVICE_ADDRESS_0          0x0E
#define CURRENT14_DEVICE_ADDRESS_1          0x0F

/*! @} */ // current14_set

/**
 * @defgroup current14_map Current 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 14 Click driver.
 */

/**
 * @addtogroup current14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 14 Click to the selected MikroBUS.
 */
#define CURRENT14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // current14_map
/*! @} */ // current14

/**
 * @brief Current 14 Click context object.
 * @details Context object definition of Current 14 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alert;         /**< Alert (data ready) pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float zero_curr_offset;     /**< Data offset for zero current value. */
    float data_resolution;      /**< Calibrated data resolution. */
    uint16_t odr;               /**< Output data rate per second. */

} current14_t;

/**
 * @brief Current 14 Click configuration object.
 * @details Configuration object definition of Current 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alert;           /**< Alert (data ready) pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} current14_cfg_t;

/**
 * @brief Current 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENT14_OK = 0,
    CURRENT14_ERROR = -1

} current14_return_value_t;

/*!
 * @addtogroup current14 Current 14 Click Driver
 * @brief API for configuring and manipulating Current 14 Click driver.
 * @{
 */

/**
 * @brief Current 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current14_cfg_setup ( current14_cfg_t *cfg );

/**
 * @brief Current 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current14_init ( current14_t *ctx, current14_cfg_t *cfg );

/**
 * @brief Current 14 default configuration function.
 * @details This function executes a default configuration of Current 14
 * Click board.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t current14_default_cfg ( current14_t *ctx );

/**
 * @brief Current 14 write reg byte function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current14_write_reg_byte ( current14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Current 14 write reg word function.
 * @details This function writes a data word starting from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current14_write_reg_word ( current14_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Current 14 read reg byte function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current14_read_reg_byte ( current14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Current 14 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t current14_get_alert_pin ( current14_t *ctx );

/**
 * @brief Current 14 set odr function.
 * @details This function sets the sensor output data rate.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - 20 Hz,
 *                  @li @c 1 - 100 Hz,
 *                  @li @c 2 - 200 Hz,
 *                  @li @c 3 - 1000 Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current14_set_odr ( current14_t *ctx, uint8_t odr );

/**
 * @brief Current 14 read data function.
 * @details This function reads the sensor raw data measurement.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @param[out] data_out : 16-bit signed RAW data output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current14_read_data ( current14_t *ctx, int16_t *data_out );

/**
 * @brief Current 14 calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no current flows through the sensor.
 */
err_t current14_calib_offset ( current14_t *ctx );

/**
 * @brief Current 14 calib resolution function.
 * @details This function calibrates the data resolution at the known load current.
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @param[in] calib_current : The known load current used for calibrating data resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when a known amount of load current flows through the sensor
 * and after calibrating zero current offset using current14_calib_offset function.
 */
err_t current14_calib_resolution ( current14_t *ctx, float calib_current );

/**
 * @brief Current 14 get current function.
 * @details This function reads the input current level [A].
 * @param[in] ctx : Click context object.
 * See #current14_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero current offset and data resolution.
 * Refer to current14_calib_offset and current14_calib_resolution functions.
 */
err_t current14_get_current ( current14_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // CURRENT14_H

/*! @} */ // current14

// ------------------------------------------------------------------------ END
