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
 * @file current6.h
 * @brief This file contains API for Current 6 Click Driver.
 */

#ifndef CURRENT6_H
#define CURRENT6_H

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
 * @addtogroup current6 Current 6 Click Driver
 * @brief API for configuring and manipulating Current 6 Click driver.
 * @{
 */

/**
 * @defgroup current6_reg Current 6 Registers List
 * @brief List of registers of Current 6 Click driver.
 */

/**
 * @addtogroup current6_reg
 * @{
 */

/**
 * @brief Current 6 register list.
 * @details Specified register list of Current 6 Click driver.
 */
#define CURRENT6_REG_CONFIGURATION                  0x00
#define CURRENT6_REG_STATUS                         0x02
#define CURRENT6_REG_THRESHOLD_OVER_CURRENT         0x04
#define CURRENT6_REG_THRESHOLD_OVER_VOLTAGE         0x05
#define CURRENT6_REG_THRESHOLD_UNDER_VOLTAGE        0x06
#define CURRENT6_REG_WAKE_UP_CURRENT                0x07
#define CURRENT6_REG_MAX_PEAK_CURRENT               0x08
#define CURRENT6_REG_FIFO_CONFIGURATION             0x0A
#define CURRENT6_REG_CURRENT_MEASUREMENT            0x0C
#define CURRENT6_REG_VOLTAGE_MEASUREMENT            0x0E
#define CURRENT6_REG_CURRENT_VOLTAGE_MEASUREMENT    0x10
#define CURRENT6_REG_INT_EN                         0x14

/*! @} */ // current6_reg

/**
 * @defgroup current6_set Current 6 Registers Settings
 * @brief Settings for registers of Current 6 Click driver.
 */

/**
 * @addtogroup current6_set
 * @{
 */

/**
 * @brief Current 6 Configuration register settings.
 * @details Specified settings for Configuration register of Current 6 Click driver.
 */
#define CURRENT6_OPMODE_STANDBY                     0x0000
#define CURRENT6_OPMODE_LOW_POWER                   0x0001
#define CURRENT6_OPMODE_SINGLE_CONVERSION           0x0002
#define CURRENT6_OPMODE_CONTINUOUS_MEASUREMENT      0x0003
#define CURRENT6_OPMODE_ACTIVE_MODE_4_SPS           0x0004
#define CURRENT6_OPMODE_ACTIVE_MODE_1_SPS           0x0005
#define CURRENT6_OPMODE_ACTIVE_MODE_0p25_SPS        0x0006
#define CURRENT6_OPMODE_ACTIVE_MODE_0p0625_SPS      0x0007
#define CURRENT6_OPMODE_ACTIVE_MODE_0p25_SPS        0x0006
#define CURRENT6_I2C_TIMEOUT_DISABLE                0x0008
#define CURRENT6_I2C_TIMEOUT_ENABLE                 0x0000
#define CURRENT6_ALERT_UNFILTERED                   0x0000
#define CURRENT6_ALERT_FILTERED                     0x0010
#define CURRENT6_PEC_ENABLE                         0x0020
#define CURRENT6_PEC_DISABLE                        0x0000
#define CURRENT6_INPUT_RANGE_10mV                   0x0040
#define CURRENT6_INPUT_RANGE_50mV                   0x0000
#define CURRENT6_ENTER_HS_MODE                      0x0080
#define CURRENT6_EXIT_HS_MODE                       0x0000
#define CURRENT6_ADC_SAMPLE_RATE_15_KSPS            0x0000
#define CURRENT6_ADC_SAMPLE_RATE_23p45_KSPS         0x0200
#define CURRENT6_ADC_SAMPLE_RATE_30_KSPS            0x0300
#define CURRENT6_ADC_SAMPLE_RATE_37p5_KSPS          0x0400
#define CURRENT6_ADC_SAMPLE_RATE_47p1_KSPS          0x0500
#define CURRENT6_ADC_SAMPLE_RATE_60_KSPS            0x0600
#define CURRENT6_ADC_SAMPLE_RATE_93p5_KSPS          0x0700
#define CURRENT6_ADC_SAMPLE_RATE_120_KSPS           0x0800
#define CURRENT6_ADC_SAMPLE_RATE_150_KSPS           0x0900
#define CURRENT6_ADC_SAMPLE_RATE_234p5_KSPS         0x0A00
#define CURRENT6_ADC_SAMPLE_RATE_375_KSPS           0x0B00
#define CURRENT6_ADC_SAMPLE_RATE_468p5_KSPS         0x0C00
#define CURRENT6_ADC_SAMPLE_RATE_750_KSPS           0x0D00
#define CURRENT6_ADC_SAMPLE_RATE_1000_KSPS          0x0E00
#define CURRENT6_ADC_SAMPLE_RATE_0p5_KSPS           0x0F00
#define CURRENT6_DIGITAL_FILTER_NO_AVG              0x0000
#define CURRENT6_DIGITAL_FILTER_AVG_8_SAMPLES       0x1000
#define CURRENT6_DIGITAL_FILTER_AVG_16_SAMPLES      0x2000
#define CURRENT6_DIGITAL_FILTER_AVG_32_SAMPLES      0x3000
#define CURRENT6_DIGITAL_FILTER_AVG_64_SAMPLES      0x4000
#define CURRENT6_DIGITAL_FILTER_AVG_128_SAMPLES     0x5000

/**
 * @brief Current 6 Status register settings.
 * @details Specified settings for Status register of Current 6 Click driver.
 */
#define CURRENT6_STATUS_WAKE_UP                     0x0001
#define CURRENT6_STATUS_CONVERSION_READY            0x0002
#define CURRENT6_STATUS_OVERFLOW_CURRENT            0x0004
#define CURRENT6_STATUS_OVERFLOW_VOLTAGE            0x0008
#define CURRENT6_STATUS_UNDERFLOW_VOLTAGE           0x0010
#define CURRENT6_STATUS_I2C_TIMEOUT                 0x0020
#define CURRENT6_STATUS_FIFO_ALARM                  0x0040
#define CURRENT6_STATUS_FIFO_OVERFLOW               0x0080
#define CURRENT6_STATUS_FIFO_DATA_COUNT_MASK        0x3F00

/**
 * @brief Current 6 FIFO configuration register settings.
 * @details Specified settings for FIFO configuration register of Current 6 Click driver.
 */
#define CURRENT6_FIFO_CFG_STORE_CURRENT_ONLY        0x0000
#define CURRENT6_FIFO_CFG_STORE_VOLTAGE_ONLY        0x0001
#define CURRENT6_FIFO_CFG_STORE_ALL                 0x0002
#define CURRENT6_FIFO_CFG_DATA_OVERFLOW_MASK        0x3F00
#define CURRENT6_FIFO_CFG_DATA_OVERFLOW_DEFAULT     0x0100
#define CURRENT6_FIFO_CFG_ROLL_OVER                 0x4000
#define CURRENT6_FIFO_CFG_FLUSH                     0x8000

/**
 * @brief Current 6 FIFO data register settings.
 * @details Specified settings for FIFO data register of Current 6 Click driver.
 */
#define CURRENT6_FIFO_DATA_VALID_32                 0x80000000
#define CURRENT6_FIFO_DATA_VALID_16                 0x8000
#define CURRENT6_FIFO_DATA_SIGN_BIT                 0x1000
#define CURRENT6_FIFO_DATA_RESOLUTION               0x0FFF

/**
 * @brief Current 6 INT enable register settings.
 * @details Specified settings for INT enable register of Current 6 Click driver.
 */
#define CURRENT6_INT_EN_WAKE_UP                     0x01
#define CURRENT6_INT_EN_CONVERSION_READY            0x02
#define CURRENT6_INT_EN_OVERFLOW_CURRENT            0x04
#define CURRENT6_INT_EN_OVERFLOW_VOLTAGE            0x08
#define CURRENT6_INT_EN_UNDERFLOW_VOLTAGE           0x10
#define CURRENT6_INT_EN_I2C_TIMEOUT                 0x20
#define CURRENT6_INT_EN_ALARM                       0x40
#define CURRENT6_INT_EN_OVERFLOW                    0x80

/**
 * @brief Current 6 current and voltage calculation values.
 * @details Specified current and voltage calculation values of Current 6 Click driver.
 */
#define CURRENT6_VOLTAGE_CALCULATION_COEFFICIENT    0.00917
#define CURRENT6_CURRENT_CALCULATION_COEFFICIENT    0.00125

/**
 * @brief Current 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Current 6 Click driver.
 */
#define CURRENT6_SET_DEV_ADDR                       0x21

/*! @} */ // current6_set

/**
 * @defgroup current6_map Current 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 6 Click driver.
 */

/**
 * @addtogroup current6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 6 Click to the selected MikroBUS.
 */
#define CURRENT6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // current6_map
/*! @} */ // current6

/**
 * @brief Current 6 Click context object.
 * @details Context object definition of Current 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */
    
    // Input pins
    digital_in_t alr;           /**< Alert pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t pec_enable;         /**< PEC enable flag */

} current6_t;

/**
 * @brief Current 6 Click configuration object.
 * @details Configuration object definition of Current 6 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  alr;            /**< Alert pin. */
    pin_name_t  en;             /**< Enable pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} current6_cfg_t;

/**
 * @brief Current 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENT6_OK = 0,
    CURRENT6_ERROR = -1

} current6_return_value_t;

/*!
 * @addtogroup current6 Current 6 Click Driver
 * @brief API for configuring and manipulating Current 6 Click driver.
 * @{
 */

/**
 * @brief Current 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current6_cfg_setup ( current6_cfg_t *cfg );

/**
 * @brief Current 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current6_init ( current6_t *ctx, current6_cfg_t *cfg );

/**
 * @brief Current 6 default configuration function.
 * @details This function executes a default configuration of Current 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t current6_default_cfg ( current6_t *ctx );

/**
 * @brief Current 6 write byte function.
 * @details This function writes one byte of data to the selected byte register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current6_write_byte ( current6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Current 6 read byte function.
 * @details This function reads one byte of data from the selected byte register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current6_read_byte ( current6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Current 6 write word function.
 * @details This function writes two bytes of data to the selected word register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current6_write_word ( current6_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Current 6 read word function.
 * @details This function reads two bytes of data from the selected word register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current6_read_word ( current6_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Current 6 read 32-bit function.
 * @details This function reads four bytes of data from the 32-bit data register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current6_read_32 ( current6_t *ctx, uint32_t *data_out );

/**
 * @brief Current 6 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t current6_get_alert_pin ( current6_t *ctx );

/**
 * @brief Current 6 read data function.
 * @details This function reads the input voltage and current measurement values.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @param[out] voltage : Voltage in Volts.
 * @param[out] current : Current in Ampers.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current6_read_data ( current6_t *ctx, float *voltage, float *current );

/**
 * @brief Current 6 get status function.
 * @details This function reads and clears the status register.
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @param[out] status : Status register value before clearing.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current6_get_status ( current6_t *ctx, uint16_t *status );

/** 
 * @brief PEC Enable function.
 * @details This function enables PEC. 
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t current6_enable_pec ( current6_t *ctx );

/** 
 * @brief PEC Disable function.
 * @details This function disables PEC. 
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t current6_disable_pec ( current6_t *ctx );

/** 
 * @brief Current 6 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state. 
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void current6_enable_device ( current6_t *ctx );

/** 
 * @brief Current 6 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state. 
 * @param[in] ctx : Click context object.
 * See #current6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void current6_disable_device ( current6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CURRENT6_H

/*! @} */ // current6

// ------------------------------------------------------------------------ END
