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
 * @file thermo27.h
 * @brief This file contains API for Thermo 27 Click Driver.
 */

#ifndef THERMO27_H
#define THERMO27_H

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
 * @addtogroup thermo27 Thermo 27 Click Driver
 * @brief API for configuring and manipulating Thermo 27 Click driver.
 * @{
 */

/**
 * @defgroup thermo27_reg Thermo 27 Registers List
 * @brief List of registers of Thermo 27 Click driver.
 */

/**
 * @addtogroup thermo27_reg
 * @{
 */

/**
 * @brief Thermo 27 description register.
 * @details Specified register for description of Thermo 27 Click driver.
 */
#define THERMO27_TEMP_RESULT_REG                    0x00
#define THERMO27_SLEW_RESULT_REG                    0x01
#define THERMO27_ALERT_STATUS_REG                   0x02
#define THERMO27_CONFIGURATION_REG                  0x03
#define THERMO27_TLOW_LIMIT_REG                     0x04
#define THERMO27_THIGH_LIMIT_REG                    0x05
#define THERMO27_HYSTERESIS_REG                     0x06
#define THERMO27_SLEW_LIMIT_REG                     0x07
#define THERMO27_UNIQUE_ID1_REG                     0x08
#define THERMO27_UNIQUE_ID2_REG                     0x09
#define THERMO27_UNIQUE_ID3_REG                     0x0A
#define THERMO27_DEVICE_ID_REG                      0x0B

/*! @} */ // thermo27_reg

/**
 * @defgroup thermo27_set Thermo 27 Registers Settings
 * @brief Settings for registers of Thermo 27 Click driver.
 */

/**
 * @addtogroup thermo27_set
 * @{
 */

/**
 * @brief Thermo 27 description setting.
 * @details Specified setting for description of Thermo 27 Click driver.
 */
#define THERMO27_CRC_MODE_ENABLED                   0x01
#define THERMO27_CRC_MODE_DISABLED                  0x00
#define THERMO27_POLYNOMIAL                         0x07
#define THERMO27_DEVICE_ID                          0x1114
#define THERMO27_TEMP_COEF                          0.0078125
#define THERMO27_LSB_VAL                            0.03125
#define THERMO27_LOW_TEMP_LIMIT_VAL                -25
#define THERMO27_HIGH_TEMP_LIMIT_VAL                80
#define THERMO27_SW_RESET                           0x06

/**
 * @brief Thermo 27 configuration setting.
 * @details Specified setting for configurating the
 * Thermo 27 Click driver.
 */
#define THERMO27_ADC_TIME_6mS_MODE_CMD              0x0000
#define THERMO27_ADC_TIME_4mS_MODE_CMD              0x0200
#define THERMO27_ADC_TIME_2mS_MODE_CMD              0x0400
#define THERMO27_ADC_TIME_1mS_MODE_CMD              0x0600
#define THERMO27_SW_RESET_CMD                       0x0100
#define THERMO27_ENABLE_AVG_CMD                     0x0080
#define THERMO27_ENABLE_CRC_CMD                     0x0040
#define THERMO27_ONE_SHOT_CMD                       0x0010
#define THERMO27_CONTINUOUS_MODE_CMD                0x0000
#define THERMO27_SHOUTDOWN_MODE_CMD                 0x0008
#define THERMO27_CONVERSION_TIME_7mS_MODE_CMD       0x0000
#define THERMO27_CONVERSION_TIME_32mS_MODE_CMD      0x0001
#define THERMO27_CONVERSION_TIME_63mS_MODE_CMD      0x0002
#define THERMO27_CONVERSION_TIME_125mS_MODE_CMD     0x0003
#define THERMO27_CONVERSION_TIME_250mS_MODE_CMD     0x0004
#define THERMO27_CONVERSION_TIME_500mS_MODE_CMD     0x0005
#define THERMO27_CONVERSION_TIME_1S_MODE_CMD        0x0006
#define THERMO27_CONVERSION_TIME_2S_MODE_CMD        0x0007

/**
 * @brief Thermo 27 alert status register flags.
 * @details Specified alert status register flags of
 * Thermo 27 Click driver.
 */
#define THERMO27_CRC_FLAG                           0x80
#define THERMO27_SLEW_STATUS                        0x40
#define THERMO27_SLEW_FLAG                          0x20
#define THERMO27_THIGH_STATUS                       0x10
#define THERMO27_TLOW_STATUS                        0x08
#define THERMO27_THIGH_FLAG                         0x04
#define THERMO27_TLOW_FLAG                          0x02
#define THERMO27_DATA_READY_FLAG                    0x01


/**
 * @brief Thermo 27 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 27 Click driver.
 */
#define THERMO27_DEVICE_ADDRESS                     0x4D
#define THERMO27_RESET_DEVICE_ADDRESS               0x00

/*! @} */ // thermo27_set

/**
 * @defgroup thermo27_map Thermo 27 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 27 Click driver.
 */

/**
 * @addtogroup thermo27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 27 Click to the selected MikroBUS.
 */
#define THERMO27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // thermo27_map
/*! @} */ // thermo27

/**
 * @brief Thermo 27 Click context object.
 * @details Context object definition of Thermo 27 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t    crc_mode;        /**< Checking if CRC mode is active.  */
    
} thermo27_t;

/**
 * @brief Thermo 27 Click configuration object.
 * @details Configuration object definition of Thermo 27 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */
    
} thermo27_cfg_t;

/**
 * @brief Thermo 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO27_OK = 0,
    THERMO27_ERROR = -1

} thermo27_return_value_t;

/*!
 * @addtogroup thermo27 Thermo 27 Click Driver
 * @brief API for configuring and manipulating Thermo 27 Click driver.
 * @{
 */

/**
 * @brief Thermo 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo27_cfg_setup ( thermo27_cfg_t *cfg );

/**
 * @brief Thermo 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_init ( thermo27_t *ctx, thermo27_cfg_t *cfg );

/**
 * @brief Thermo 27 default configuration function.
 * @details This function executes a default configuration of Thermo 27
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo27_default_cfg ( thermo27_t *ctx );

/**
 * @brief Thermo 27 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_generic_write ( thermo27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Thermo 27 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_generic_read ( thermo27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Thermo 27 register writing function.
 * @details This function writes a 16 bits of data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_write_register ( thermo27_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Thermo 27 register reading function.
 * @details This function reads a 16 bits of data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_read_register ( thermo27_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Thermo 27 get device id function.
 * @details This function reads a device id from
 * the register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[out] device_id : Read device id.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_get_device_id ( thermo27_t *ctx, uint16_t *device_id );

/**
 * @brief Thermo 27 software reset function.
 * @details This function is used to perform software reset.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_sw_reset ( thermo27_t *ctx );

/**
 * @brief Thermo 27 get read temperature function.
 * @details This function reads a temperature from the register by using 
 * I2C serial interface. Temperature is converted and returned in degC.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[out] temp_out : Temperature in degC.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_read_temp ( thermo27_t *ctx, float *temp_out );

/**
 * @brief Thermo 27 enable CRC function.
 * @details This function sets device in CRC mode. CRC is generated and added as part
 * of the read and write functions.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_enable_crc ( thermo27_t *ctx );

/**
 * @brief Thermo 27 set low temperature limit function.
 * @details This function is used to set low temperature limit.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] low_temp_limit : Low temperature limit in degC.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function ragde input is ±256 degC.
 */
err_t thermo27_set_low_temp_limit ( thermo27_t *ctx, float low_temp_limit );

/**
 * @brief Thermo 27 set high temperature limit function.
 * @details This function is used to set high temperature limit.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] high_temp_limit : High temperature limit in degC.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function ragde input is ±256 degC.
 */
err_t thermo27_set_high_temp_limit ( thermo27_t *ctx, float high_temp_limit );

/**
 * @brief Thermo 27 set hysteresis function.
 * @details This function is used to set temperature high hysteresis and temperature low hysteresis.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] thigh_hyst : High temperature hysteresis.
 * @param[in] tlow_hyst : Low temperature hysteresis.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_set_hysteresis ( thermo27_t *ctx, uint8_t thigh_hyst, uint8_t tlow_hyst );

/**
 * @brief Thermo 27 set slew limit function.
 * @details This function is used to set temperature slew limit.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[in] slew_limit : Input temperature slew limit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function ragde input is from 0 degC to 256 degC.
 */
err_t thermo27_set_slew_limit ( thermo27_t *ctx, float slew_limit );

/**
 * @brief Thermo 27 get alert register staus function.
 * @details This function is used to read alert register data.
 * @param[in] ctx : Click context object.
 * See #thermo27_t object definition for detailed explanation.
 * @param[out] register_flags : Read data from the alert register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo27_get_alert_reg ( thermo27_t *ctx, uint8_t *register_flags );

#ifdef __cplusplus
}
#endif
#endif // THERMO27_H

/*! @} */ // thermo27

// ------------------------------------------------------------------------ END
