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
 * @file barometer10.h
 * @brief This file contains API for Barometer 10 Click Driver.
 */

#ifndef BAROMETER10_H
#define BAROMETER10_H

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

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup barometer10 Barometer 10 Click Driver
 * @brief API for configuring and manipulating Barometer 10 Click driver.
 * @{
 */

/**
 * @defgroup barometer10_reg Barometer 10 Registers List
 * @brief List of registers of Barometer 10 Click driver.
 */

/**
 * @addtogroup barometer10_reg
 * @{
 */

/**
 * @brief Barometer 10 description register.
 * @details Specified register for description of Barometer 10 Click driver.
 */
#define BAROMETER10_REG_INTERRUPT_CFG              0x0B
#define BAROMETER10_REG_THS_P_L                    0x0C
#define BAROMETER10_REG_THS_P_H                    0x0D
#define BAROMETER10_REG_IF_CTRL                    0x0E
#define BAROMETER10_REG_WHO_AM_I                   0x0F
#define BAROMETER10_REG_CTRL_REG1                  0x10
#define BAROMETER10_REG_CTRL_REG2                  0x11
#define BAROMETER10_REG_CTRL_REG3                  0x12
#define BAROMETER10_REG_CTRL_REG4                  0x13
#define BAROMETER10_REG_FIFO_CTRL                  0x14
#define BAROMETER10_REG_FIFO_WTM                   0x15
#define BAROMETER10_REG_REF_P_L                    0x16
#define BAROMETER10_REG_REF_P_H                    0x17
#define BAROMETER10_REG_I3C_IF_CTRL_ADD            0x19
#define BAROMETER10_REG_RPDS_L                     0x1A
#define BAROMETER10_REG_RPDS_H                     0x1B
#define BAROMETER10_REG_INT_SOURCE                 0x24
#define BAROMETER10_REG_FIFO_STATUS1               0x25
#define BAROMETER10_REG_FIFO_STATUS2               0x26
#define BAROMETER10_REG_STATUS                     0x27
#define BAROMETER10_REG_PRESS_OUT_XL               0x28
#define BAROMETER10_REG_PRESS_OUT_L                0x29
#define BAROMETER10_REG_PRESS_OUT_H                0x2A
#define BAROMETER10_REG_TEMP_OUT_L                 0x2B
#define BAROMETER10_REG_TEMP_OUT_H                 0x2C
#define BAROMETER10_REG_FIFO_DATA_OUT_PRESS_XL     0x78
#define BAROMETER10_REG_FIFO_DATA_OUT_PRESS_L      0x79
#define BAROMETER10_REG_FIFO_DATA_OUT_PRESS_H      0x7A

/*! @} */ // barometer10_reg

/**
 * @defgroup barometer10_set Barometer 10 Registers Settings
 * @brief Settings for registers of Barometer 10 Click driver.
 */

/**
 * @addtogroup barometer10_set
 * @{
 */

/**
 * @brief Barometer 10 description BAROMETER10_REG_WHO_AM_I register value.
 * @details Specified BAROMETER10_REG_WHO_AM_I register value for description of Barometer 10 Click driver.
 */
#define BAROMETER10_DEVICE_ID                      0xB4

/**
 * @brief Barometer 10 description BAROMETER10_REG_CTRL_REG1 register value.
 * @details Specified BAROMETER10_REG_CTRL_REG1 register value for description of Barometer 10 Click driver.
 */
#define BAROMETER10_ODR_ONE_SHOT                   0x00
#define BAROMETER10_ODR_1_Hz                       0x01
#define BAROMETER10_ODR_4_Hz                       0x02
#define BAROMETER10_ODR_10_Hz                      0x03
#define BAROMETER10_ODR_25_Hz                      0x04
#define BAROMETER10_ODR_50_Hz                      0x05
#define BAROMETER10_ODR_75_Hz                      0x06
#define BAROMETER10_ODR_100_Hz                     0x07
#define BAROMETER10_ODR_200_Hz                     0x08
#define BAROMETER10_AVG_4                          0x00
#define BAROMETER10_AVG_8                          0x01
#define BAROMETER10_AVG_16                         0x02
#define BAROMETER10_AVG_32                         0x03
#define BAROMETER10_AVG_64                         0x04
#define BAROMETER10_AVG_128                        0x05
#define BAROMETER10_AVG_512                        0x07

/**
 * @brief Barometer 10 description BAROMETER10_REG_CTRL_REG2 register value.
 * @details Specified BAROMETER10_REG_CTRL_REG2 register value for description of Barometer 10 Click driver.
 */
#define BAROMETER10_FS_MODE_1260_hPa               0x00
#define BAROMETER10_FS_MODE_4060_hPa               0x01
#define BAROMETER10_LFPF_CFG_ODR4                  0x00
#define BAROMETER10_LFPF_CFG_ODR9                  0x01
#define BAROMETER10_EN_LPFP_DISABLE                0x00
#define BAROMETER10_EN_LPFP_ENABLE                 0x01
#define BAROMETER10_BDU_CONTINUOUS_UPDATE          0x00
#define BAROMETER10_BDU_NO_UPDATE_UNTIL_READ       0x01
#define BAROMETER10_SWRESET_BIT_MASK               0x02
#define BAROMETER10_ONESHOT_IDLE_MODE              0x00
#define BAROMETER10_ONESHOT_NEW_SET_ACQUIRED       0x01

/**
 * @brief Barometer 10 description BAROMETER10_REG_CTRL_REG3 register value.
 * @details Specified BAROMETER10_REG_CTRL_REG3 register value for description of Barometer 10 Click driver.
 */
#define BAROMETER10_INT_H_L_ACTIVE_HIGH            0x00
#define BAROMETER10_INT_H_L_ACTIVE_LOW             0x01
#define BAROMETER10_IF_ADD_INC_DISABLE             0x00
#define BAROMETER10_IF_ADD_INC_ENABLE              0x01

/**
 * @brief Barometer 10 description BAROMETER10_REG_CTRL_REG4 register value.
 * @details Specified BAROMETER10_REG_CTRL_REG4 register value for description of Barometer 10 Click driver.
 */
#define BAROMETER10_DRDY_PLS_DISABLE               0x00
#define BAROMETER10_DRDY_PLS_ENABLE                0x01
#define BAROMETER10_DRDY_DISABLE                   0x00
#define BAROMETER10_DRDY_ENABLE                    0x01
#define BAROMETER10_INT_EN_DISABLE                 0x00
#define BAROMETER10_INT_EN_ENABLE                  0x01

/**
 * @brief Barometer 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 10 Click driver.
 */
#define BAROMETER10_DEVICE_ADDRESS_GND             0x5C
#define BAROMETER10_DEVICE_ADDRESS_VCC             0x5D

/*! @} */ // barometer10_set

/**
 * @defgroup barometer10_map Barometer 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 10 Click driver.
 */

/**
 * @addtogroup barometer10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 10 Click to the selected MikroBUS.
 */
#define BAROMETER10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // barometer10_map
/*! @} */ // barometer10

/**
 * @brief Barometer 10 Click context object.
 * @details Context object definition of Barometer 10 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} barometer10_t;

/**
 * @brief Barometer 10 Click configuration object.
 * @details Configuration object definition of Barometer 10 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;        /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} barometer10_cfg_t;

/**
 * @brief Barometer 10 Click sensor configuration object.
 * @details Sensor configuration object definition of Barometer 10 Click driver.
 */
typedef struct
{
    uint8_t odr;           /**< Output data rate selection. */
    uint8_t avg;           /**< Average selection. */
    uint8_t fs_mode;       /**< Full-scale selection. */
    uint8_t lfpf_cfg;      /**< Low-pass filter configuration. */
    uint8_t en_lpfp;       /**< Enable low-pass filter on pressure data. */
    uint8_t bdu;           /**< Block data update. */
    uint8_t oneshot;       /**< Enable one-shot mode. */
    uint8_t int_h_l;       /**< Select interrupt active-high, active-low. */
    uint8_t if_add_inc;    /**< Automatically incremented. */
    uint8_t drdy_pls;      /**< Data-ready pulsed on INT_DRDY pin. */
    uint8_t drdy;          /**< Date-ready signal on INT_DRDY pin. */
    uint8_t int_en;        /**< Interrupt signal on INT_DRDY pin. */

} barometer10_sensor_cfg_t;

/**
 * @brief Barometer 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER10_OK = 0,
    BAROMETER10_ERROR = -1

} barometer10_return_value_t;

/*!
 * @addtogroup barometer10 Barometer 10 Click Driver
 * @brief API for configuring and manipulating Barometer 10 Click driver.
 * @{
 */

/**
 * @brief Barometer 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer10_cfg_setup ( barometer10_cfg_t *cfg );

/**
 * @brief Barometer 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_init ( barometer10_t *ctx, barometer10_cfg_t *cfg );

/**
 * @brief Barometer 10 default configuration function.
 * @details This function executes a default configuration of Barometer 10
 * Click board.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer10_default_cfg ( barometer10_t *ctx );

/**
 * @brief Barometer 10 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_generic_write ( barometer10_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 10 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_generic_read ( barometer10_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 10 software reset function.
 * @details This function perform software reset 
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_sw_reset ( barometer10_t *ctx );

/**
 * @brief Barometer 10 gets device ID function.
 * @details This function reads a BAROMETER10_REG_WHO_AM_I register 
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[out] device_id : Device ID values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_get_device_id ( barometer10_t *ctx, uint8_t *device_id );

/**
 * @brief Barometer 10 gets configuration function.
 * @details This function gets sensor configuration data object
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[out] config : Sensor configuration object.
 * See barometer10_sensor_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_get_config ( barometer10_t *ctx, barometer10_sensor_cfg_t *config );

/**
 * @brief Barometer 10 set configuration function.
 * @details This function set sensor configuration data object
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[in] config : Sensor configuration object.
 * See barometer10_sensor_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_set_config ( barometer10_t *ctx, barometer10_sensor_cfg_t config );

/**
 * @brief Barometer 10 trigger one-shot function.
 * @details This function sets the configuration for a one-shot trigger
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_trigger_one_shot ( barometer10_t *ctx );

/**
 * @brief Barometer 10 gets pressure output function.
 * @details This function reads a pressure output raw values
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[out] pressure_raw : Signed 24-bit pressure output raw values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_get_pressure_output ( barometer10_t *ctx, int32_t *pressure_raw );

/**
 * @brief Barometer 10 gets temperature output function.
 * @details This function reads a temperature output raw values
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[out] pressure_raw : Signed 16-bit temperature output raw values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_get_temperature_output ( barometer10_t *ctx, int16_t *temperature_raw );

/**
 * @brief Barometer 10 gets pressure function.
 * @details This function reads a pressure data in hPa/mbar
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data [hPa/mbar].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_get_pressure ( barometer10_t *ctx, float *pressure );

/**
 * @brief Barometer 10 gets temperature function.
 * @details This function reads a temperature data in degree Celsius
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data [deg C].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer10_get_temperature ( barometer10_t *ctx, float *temperature );

/**
 * @brief Barometer 10 gets interrupt function.
 * @details This function get states of the Interrupt ( INT ) pin
 * of the LPS28DFW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with water-resistant package
 * on the Barometer 10 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer10_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t barometer10_get_int_pin ( barometer10_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER10_H

/*! @} */ // barometer10

// ------------------------------------------------------------------------ END
