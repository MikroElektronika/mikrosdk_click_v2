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
 * @file color17.h
 * @brief This file contains API for Color 17 Click Driver.
 */

#ifndef COLOR17_H
#define COLOR17_H

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
 * @addtogroup color17 Color 17 Click Driver
 * @brief API for configuring and manipulating Color 17 Click driver.
 * @{
 */

/**
 * @defgroup color17_reg Color 17 Registers List
 * @brief List of registers of Color 17 Click driver.
 */

/**
 * @addtogroup color17_reg
 * @{
 */

/**
 * @brief Color 17 description register.
 * @details Specified register for description of Color 17 Click driver.
 */
#define COLOR17_REG_CH0_EXP_RESMSB             0x00
#define COLOR17_REG_CH0_RESMSB_CNT_CRC         0x01
#define COLOR17_REG_CH1_EXP_RES_MSB            0x02
#define COLOR17_REG_CH1_RESMSB_CNT_CRC         0x03
#define COLOR17_REG_CH2_EXP_RES_MSB            0x04
#define COLOR17_REG_CH2_RESMSB_CNT_CRC         0x05
#define COLOR17_REG_CH3_EXP_RES_MSB            0x06
#define COLOR17_REG_CH4_RESMSB_CNT_CRC         0x07
#define COLOR17_REG_THLD_EXP_RES_L             0x08
#define COLOR17_REG_THLD_EXP_RES_H             0x09
#define COLOR17_REG_CONFIG_0                   0x0A
#define COLOR17_REG_CONFIG_1                   0x0B
#define COLOR17_REG_CONFIG_2                   0x0C
#define COLOR17_REG_DEVICE_ID                  0x11

/*! @} */ // color17_reg

/**
 * @defgroup color17_set Color 17 Registers Settings
 * @brief Settings for registers of Color 17 Click driver.
 */

/**
 * @addtogroup color17_set
 * @{
 */

/**
 * @brief Color 17 description device ID value.
 * @details Specified device ID value of Color 17 Click driver.
 */
#define COLOR17_DEVICE_ID                      0x0821u

/**
 * @brief Color 17 description COLOR17_REG_CONFIG_0 register values.
 * @details Specified COLOR17_REG_CONFIG_0 register values of Color 17 Click driver.
 */
#define COLOR17_CONFIG_0_QWAKE_DIS             0x00
#define COLOR17_CONFIG_0_QWAKE_EN              0x01
#define COLOR17_CONFIG_0_RANGE_2_2KLUX         0x00
#define COLOR17_CONFIG_0_RANGE_4_5KLUX         0x01
#define COLOR17_CONFIG_0_RANGE_9KLUX           0x02
#define COLOR17_CONFIG_0_RANGE_18KLUX          0x03
#define COLOR17_CONFIG_0_RANGE_36KLUX          0x04
#define COLOR17_CONFIG_0_RANGE_72KLUX          0x05
#define COLOR17_CONFIG_0_RANGE_144KLUX         0x06
#define COLOR17_CONFIG_0_RANGE_AUTO            0x0C
#define COLOR17_CONFIG_0_CONV_600US            0x00
#define COLOR17_CONFIG_0_CONV_1_MS             0x01
#define COLOR17_CONFIG_0_CONV_1_8MS            0x02
#define COLOR17_CONFIG_0_CONV_3_4MS            0x03
#define COLOR17_CONFIG_0_CONV_6_5MS            0x04
#define COLOR17_CONFIG_0_CONV_12_7MS           0x05
#define COLOR17_CONFIG_0_CONV_25MS             0x06
#define COLOR17_CONFIG_0_CONV_50MS             0x07
#define COLOR17_CONFIG_0_CONV_100MS            0x08
#define COLOR17_CONFIG_0_CONV_200MS            0x09
#define COLOR17_CONFIG_0_CONV_400MS            0x0A
#define COLOR17_CONFIG_0_CONV_800MS            0x0B
#define COLOR17_CONFIG_0_OP_MODE_PD            0x00
#define COLOR17_CONFIG_0_OP_MODE_F_ONESHOT     0x01
#define COLOR17_CONFIG_0_OP_MODE_ONESHOT       0x02
#define COLOR17_CONFIG_0_OP_MODE_CONTINUOUS    0x03
#define COLOR17_CONFIG_0_LATCH_DIS             0x00
#define COLOR17_CONFIG_0_LATCH_EN              0x01
#define COLOR17_CONFIG_0_INT_POL_LOW           0x00
#define COLOR17_CONFIG_0_INT_POL_HIGH          0x01
#define COLOR17_CONFIG_0_FAULT_COUNT_0         0x00
#define COLOR17_CONFIG_0_FAULT_COUNT_2         0x01
#define COLOR17_CONFIG_0_FAULT_COUNT_4         0x02
#define COLOR17_CONFIG_0_FAULT_COUNT_8         0x03

/**
 * @brief Color 17 description COLOR17_REG_CONFIG_1 register values.
 * @details Specified COLOR17_REG_CONFIG_1 register values of Color 17 Click driver.
 */
#define COLOR17_CONFIG_1_MUST_READ_WRITE       0x8000u
#define COLOR17_CONFIG_1_THRESHOLD_CH0         0x00
#define COLOR17_CONFIG_1_THRESHOLD_CH1         0x01
#define COLOR17_CONFIG_1_THRESHOLD_CH2         0x02
#define COLOR17_CONFIG_1_THRESHOLD_CH3         0x03
#define COLOR17_CONFIG_1_INT_DIR_INPUT         0x00
#define COLOR17_CONFIG_1_INT_DIR_OUTPUT        0x01
#define COLOR17_CONFIG_1_INT_CFG_SMBUS_ALR     0x00
#define COLOR17_CONFIG_1_INT_CFG_NEXT_CH       0x01
#define COLOR17_CONFIG_1_INT_CFG_ALL_CH        0x03
#define COLOR17_CONFIG_1_I2C_BURST_DISABLE     0x00
#define COLOR17_CONFIG_1_I2C_BURST_ENABLE      0x01

/**
 * @brief Color 17 description COLOR17_REG_CONFIG_2 register values.
 * @details Specified COLOR17_REG_CONFIG_2 register values of Color 17 Click driver.
 */
#define COLOR17_CONFIG_2_FLAG_DISABLE          0x00
#define COLOR17_CONFIG_2_FLAG_ENABLE           0x01

/**
 * @brief Color 17 description channel number values.
 * @details Specified channel number values of Color 17 Click driver.
 */
#define COLOR17_SEL_CHANNEL_0                  0x00
#define COLOR17_SEL_CHANNEL_1                  0x01
#define COLOR17_SEL_CHANNEL_2                  0x02
#define COLOR17_SEL_CHANNEL_3                  0x03

/**
 * @brief Color 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 17 Click driver.
 */
#define COLOR17_DEVICE_ADDRESS_GND             0x44
#define COLOR17_DEVICE_ADDRESS_VCC             0x45

/*! @} */ // color17_set

/**
 * @defgroup color17_map Color 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 17 Click driver.
 */

/**
 * @addtogroup color17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 17 Click to the selected MikroBUS.
 */
#define COLOR17_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color17_map
/*! @} */ // color17

/**
 * @brief Color 17 Click context object.
 * @details Context object definition of Color 17 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} color17_t;

/**
 * @brief Color 17 Click configuration object.
 * @details Configuration object definition of Color 17 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} color17_cfg_t;

/**
 * @brief Color 17 Click configuration data object.
 * @details Configuration data object definition of Color 17 Click driver.
 */
typedef struct
{
    uint8_t qwake;          /**< Quick Wake-up from Standby in one shot mode. */
    uint8_t range;          /**< Controls the full-scale light level range of the device. */
    uint8_t conv_time;      /**< Controls the device conversion time. */
    uint8_t op_mode;        /**< Controls device mode of operation. */
    uint8_t latch;          /**< Controls the functionality of the interrupt reporting mechanisms. */
    uint8_t int_pol;        /**< Controls the polarity or active state of the INT pin. */
    uint8_t fault_cnt;      /**< Fault count register instructs the device. */
    uint8_t thld_ch_sel;    /**< Channel select for threshold logic. */
    uint8_t int_dir;        /**< Determines the direction of the INT pin. */
    uint8_t int_cfg;        /**< Controls the output interrupt mechanism after end of conversion. */
    uint8_t i2c_burst;      /**< Enables I2C burst mode minimizing I2C read cycles by auto incrementing read. */

} color17_config_t;

/**
 * @brief Color 17 Click status flag object.
 * @details Status flag data object definition of Color 17 Click driver.
 */
typedef struct
{
    uint8_t ovld_flag;          /**< Indicates when an overflow condition occurs in the data conversion process. */
    uint8_t conv_ready_flag;    /**< Conversion ready flag indicates when a conversion completes. */
    uint8_t flag_h;             /**< Flag high register identifies that the result of a conversion is measurement. */
    uint8_t flag_l;             /**< Flag low register identifies that the result of a conversion is measurement. */

} color17_status_flag_t;

/**
 * @brief Color 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR17_OK = 0,
    COLOR17_ERROR = -1

} color17_return_value_t;

/*!
 * @addtogroup color17 Color 17 Click Driver
 * @brief API for configuring and manipulating Color 17 Click driver.
 * @{
 */

/**
 * @brief Color 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color17_cfg_setup ( color17_cfg_t *cfg );

/**
 * @brief Color 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_init ( color17_t *ctx, color17_cfg_t *cfg );

/**
 * @brief Color 17 default configuration function.
 * @details This function executes a default configuration of Color 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color17_default_cfg ( color17_t *ctx );

/**
 * @brief Color 17 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_generic_write ( color17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_generic_read ( color17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Color 17write register function.
 * @details This function writes 16-bit data to the selected register
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_write_reg ( color17_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Color 17 read register function.
 * @details This function reads a datafrom the selected register 
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_read_reg ( color17_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Color 17 gets device ID function.
 * @details This function reads a device ID
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_get_device_id ( color17_t *ctx, uint16_t *device_id );

/**
 * @brief Color 17 set the configuration function.
 * @details This function executes a configuration of the 
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[in] config : Sensor configuration object.
 * See color17_config_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_set_config ( color17_t *ctx, color17_config_t config );

/**
 * @brief Color 17 gets the status flag function.
 * @details This function reads the status flag
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[out] status_flag : Sensor status flag object.
 * See color17_status_flag_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_get_status_flag ( color17_t *ctx, color17_status_flag_t *status_flag );

/**
 * @brief Color 17 gets the channel measurements data function.
 * @details This function reads the measurements values of the selected channel
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[out] adc_codes : 28-bit ADC codes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_get_ch_measurement ( color17_t *ctx, uint8_t ch, uint32_t *adc_codes );

/**
 * @brief Color 17 gets light and color measurement data function.
 * @details This function reads the measurements values of the all channels
 * by reading the device measures light on 4 independent channels 
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[out] adc_codes : 28-bit ADC codes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_get_measurement ( color17_t *ctx, uint32_t *adc_codes );

/**
 * @brief Color 17 gets correlated color temperature data function.
 * @details This function reads the measurements values of the all channels
 * and calculate the correlated color temperature (CCT) and lux
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @param[out] cct : Correlated color temperature.
 * @param[out] light_intensity : Light intensity (Lux).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color17_get_cct ( color17_t *ctx, float *cct, float *light_intensity );

/**
 * @brief Color 17 gets interrupt function.
 * @details This function gets states of the Interrupt ( INT ) pin
 * of the OPT4048DTSR, High-speed high-precision tristimulus XYZ color sensor
 * on the Color 17 click board™. 
 * @param[in] ctx : Click context object.
 * See #color17_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t color17_get_int_pin ( color17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // COLOR17_H

/*! @} */ // color17

// ------------------------------------------------------------------------ END
