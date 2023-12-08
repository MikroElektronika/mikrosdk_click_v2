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
 * @file ambient20.h
 * @brief This file contains API for Ambient 20 Click Driver.
 */

#ifndef AMBIENT20_H
#define AMBIENT20_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ambient20 Ambient 20 Click Driver
 * @brief API for configuring and manipulating Ambient 20 Click driver.
 * @{
 */

/**
 * @defgroup ambient20_reg Ambient 20 Registers List
 * @brief List of registers of Ambient 20 Click driver.
 */

/**
 * @addtogroup ambient20_reg
 * @{
 */

/**
 * @brief Ambient 20 description register.
 * @details Specified register for description of Ambient 20 Click driver.
 */
#define AMBIENT20_SYSTEM_CONTROL_REG        0x40
#define AMBIENT20_MODE_CONTROL1_REG         0x41
#define AMBIENT20_MODE_CONTROL2_REG         0x42
#define AMBIENT20_MODE_CONTROL3_REG         0x43
#define AMBIENT20_DATA0_LSB_REG             0x50
#define AMBIENT20_DATA0_MSB_REG             0x51
#define AMBIENT20_DATA1_LSB_REG             0x52
#define AMBIENT20_DATA1_MSB_REG             0x53
#define AMBIENT20_MANUFACTURER_ID_REG       0x92

/*! @} */ // ambient20_reg

/**
 * @defgroup ambient20_set Ambient 20 Registers Settings
 * @brief Settings for registers of Ambient 20 Click driver.
 */

/**
 * @addtogroup ambient20_set
 * @{
 */

/**
 * @brief Ambient 20 description setting.
 * @details Specified setting for description of Ambient 20 Click driver.
 */
#define AMBIENT20_GAIN_X1                   0x02
#define AMBIENT20_GAIN_X32                  0x0A
#define AMBIENT20_GAIN_X256                 0x0C
#define AMBIENT20_100mS_MODE                0x00
#define AMBIENT20_55mS_MODE                 0x01
#define AMBIENT20_VALID_MASK                0x80
#define AMBIENT20_ENABLE                    0x01
#define AMBIENT20_DISABLE                   0x00
#define AMBIENT20_MANUFACTURER_ID           0xE0
#define AMBIENT20_PART_ID                   0x12
#define AMBIENT20_PART_ID_MASK              0x3F

/**
 * @brief Ambient 20 data conversion coefficients.
 * @details Specified setting for data conversion of Ambient 20 Click driver.
 * These coefficients are gathered from the datasheet of the device by dividing 
 * the typical data count value by the lux value it represents.
 */
#define AMBIENT20_DATA0_CONVERSION_COEF     0.169491525
#define AMBIENT20_DATA1_CONVERSION_COEF     0.689655172

/**
 * @brief Ambient 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 20 Click driver.
 */
#define AMBIENT20_DEVICE_ADDRESS        0x38

/*! @} */ // ambient20_set

/**
 * @defgroup ambient20_map Ambient 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 20 Click driver.
 */

/**
 * @addtogroup ambient20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 20 Click to the selected MikroBUS.
 */
#define AMBIENT20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ) 
  
/*! @} */ // ambient20_map
/*! @} */ // ambient20

/**
 * @brief Ambient 20 Click context object.
 * @details Context object definition of Ambient 20 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */
    
    uint8_t data0_gain;
    uint8_t data1_gain;

} ambient20_t;

/**
 * @brief Ambient 20 Click configuration object.
 * @details Configuration object definition of Ambient 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ambient20_cfg_t;

/**
 * @brief Ambient 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT20_OK = 0,
    AMBIENT20_ERROR = -1

} ambient20_return_value_t;

/*!
 * @addtogroup ambient20 Ambient 20 Click Driver
 * @brief API for configuring and manipulating Ambient 20 Click driver.
 * @{
 */

/**
 * @brief Ambient 20 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient20_cfg_setup ( ambient20_cfg_t *cfg );

/**
 * @brief Ambient 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_init ( ambient20_t *ctx, ambient20_cfg_t *cfg );

/**
 * @brief Ambient 20 default configuration function.
 * @details This function executes a default configuration of Ambient 20
 * click board.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient20_default_cfg ( ambient20_t *ctx );

/**
 * @brief Ambient 20 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_generic_write ( ambient20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Ambient 20 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_generic_read ( ambient20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Ambient 20 software reset function.
 * @details This function is performing software reset by setting SW_RESET bit 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_sw_reset ( ambient20_t *ctx );

/**
 * @brief Ambient 20 read manufacturer id function.
 * @details This function is performing reading of the manufacturer id 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[out] manufacturer_id : Read manufacturer id.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_get_manufacturer_id ( ambient20_t *ctx, uint8_t *manufacturer_id );

/**
 * @brief Ambient 20 read part id function.
 * @details This function is performing reading of the part id 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[out] part_id : Read part id.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_get_part_id ( ambient20_t *ctx, uint8_t *part_id );

/**
 * @brief Ambient 20 enable wait mode function.
 * @details This function is enableing wait mode. Wait mode can be enabled only when MEAS_MODE is 
 * set in 55mS mode. When this mode is active, measurement time is same as in 100mS mode. 
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait mode can be enabled only when MEAS_MODE is set in 55mS mode.
 */
err_t ambient20_enable_wait_mode ( ambient20_t *ctx );

/**
 * @brief Ambient 20 disable wait mode function.
 * @details This function disables wait mode. Wait mode can be enabled only when MEAS_MODE is 
 * set in 55mS mode. When this mode is active, measurement time is same as in 100mS mode. 
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait mode can be enabled only when MEAS_MODE is set in 55mS mode.
 */
err_t ambient20_disable_wait_mode ( ambient20_t *ctx );

/**
 * @brief Ambient 20 set measurement mode function.
 * @details This function is used to set measurement mode for DATA0 and DATA0, provided modes are
 * 100mS and 55mS mode.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[in] meas_mode : Measurement mode value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_set_meas_mode ( ambient20_t *ctx, uint8_t meas_mode );

/**
 * @brief Ambient 20 set data gain function.
 * @details This function is used to set ADC data gain. This function only uses 3 alredy 
 * provided modes, other settings are prohibited.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[in] data0_gain : Data 0 gain value.
 * @param[in] data1_gain : Data 1 gain value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Only use provided gain values, other values are prohibited.
 */
err_t ambient20_set_gain ( ambient20_t *ctx, uint8_t data0_gain, uint8_t data1_gain );

/**
 * @brief Ambient 20 enable measurements function.
 * @details This function is used to set the Ambient 20 Click into measurment mode.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_enable_meas ( ambient20_t *ctx );

/**
 * @brief Ambient 20 disable measurements function.
 * @details This function is used to disable measurment mode of the Ambient 20 Click.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_disable_meas ( ambient20_t *ctx );

/**
 * @brief Ambient 20 check valid bit function.
 * @details This function is used to check valid bit of the Ambient 20 Click. Valid bit is used to 
 * check status of the AMBIENT20_MODE_CONTROL1_REG, AMBIENT20_MODE_CONTROL2_REG and 
 * AMBIENT20_MODE_CONTROL3_REG data.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @return @li @c  0 - Measurment data is updated,
 *         @li @c -1 - Measurment data is not updated.
 * @note None.
 */
err_t ambient20_check_valid ( ambient20_t *ctx );

/**
 * @brief Ambient 20 read data0 function.
 * @details This function is used to read data0 channel data.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[out] data0_out : Data0 read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_read_data0 ( ambient20_t *ctx, uint16_t *data0_out );

/**
 * @brief Ambient 20 read data1 function.
 * @details This function is used to read data1 channel data.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[out] data1_out : Data1 read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_read_data1 ( ambient20_t *ctx, uint16_t *data1_out );

/**
 * @brief Ambient 20 read light function.
 * @details This function is used to read ambient lighting data of both channels.
 * @param[in] ctx : Click context object.
 * See #ambient20_t object definition for detailed explanation.
 * @param[out] data0_out : Data0 read data.
 * @param[out] data1_out : Data1 read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient20_get_data_lux ( ambient20_t *ctx, float *data0_out ,float *data1_out );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT20_H

/*! @} */ // ambient20

// ------------------------------------------------------------------------ END
