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
 * @file cooler.h
 * @brief This file contains API for Cooler Click Driver.
 */

#ifndef COOLER_H
#define COOLER_H

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
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup cooler Cooler Click Driver
 * @brief API for configuring and manipulating Cooler Click driver.
 * @{
 */

/**
 * @defgroup cooler_reg Cooler Registers List
 * @brief List of registers of Cooler Click driver.
 */

/**
 * @addtogroup cooler_reg
 * @{
 */

/**
 * @brief Cooler description register.
 * @details Specified register for description of Cooler Click driver.
 */
#define COOLER_REG_SENSOR_VOLTAGE            0x00
#define COOLER_REG_LOCAL_TEMPERATURE         0x01
#define COOLER_REG_CONFIGURATION             0x02
#define COOLER_REG_OBJECT_TEMPERATURE        0x03
#define COOLER_REG_STATUS                    0x04
#define COOLER_REG_STATUS_MASK_AND_ENABLE    0x05
#define COOLER_REG_OBJECT_HIGH_LIMIT_TEMP    0x06
#define COOLER_REG_OBJECT_LOW_LIMIT_TEMP     0x07
#define COOLER_REG_LOCAL_HIGH_LIMIT_TEMP     0x08
#define COOLER_REG_LOCAL_LOW_LIMIT_TEMP      0x09
#define COOLER_REG_S0_COEFFICIENT            0x0A
#define COOLER_REG_A0_COEFFICIENT            0x0B
#define COOLER_REG_A1_COEFFICIENT            0x0C
#define COOLER_REG_B0_COEFFICIENT            0x0D
#define COOLER_REG_B1_COEFFICIENT            0x0E
#define COOLER_REG_B2_COEFFICIENT            0x0F
#define COOLER_REG_C_COEFFICIENT             0x10
#define COOLER_REG_TC0_COEFFICIENT           0X11
#define COOLER_REG_TC1_COEFFICIENT           0x12
#define COOLER_REG_MANUFACTURER_ID           0x1E
#define COOLER_REG_DEVICE_ID                 0x1F
#define COOLER_REG_MEMORY_ACCESS             0x2A

/*! @} */ // cooler_reg

/**
 * @defgroup cooler_set Cooler Registers Settings
 * @brief Settings for registers of Cooler Click driver.
 */

/**
 * @addtogroup cooler_set
 * @{
 */

/**
 * @brief Cooler configuration setting.
 * @details Specified configuration setting of Cooler Click driver.
 */
#define COOLER_CFG_MODEON                    0x1000u
#define COOLER_CFG_RESET                     0x8000u
#define COOLER_CFG_1SAMPLE                   0x0000u
#define COOLER_CFG_2SAMPLE                   0x0200u
#define COOLER_CFG_4SAMPLE                   0x0400u
#define COOLER_CFG_8SAMPLE                   0x0600u
#define COOLER_CFG_16SAMPLE                  0x0800u
#define COOLER_CFG_ALERTEN                   0x0100u
#define COOLER_CFG_ALERTF                    0x0080u
#define COOLER_CFG_TRANSC                    0x0040u

/**
 * @brief Cooler status mask and enable setting.
 * @details Specified status mask and enable setting of Cooler Click driver.
 */
#define COOLER_STAT_ALERTEN                  0x8000u
#define COOLER_STAT_CRTEN                    0x4000u

/**
 * @brief Cooler device ID value.
 * @details Device ID value of Cooler Click driver.
 */
#define COOLER_DEVICE_ID                     0x0078u

/**
 * @brief Cooler ADC setting.
 * @details Specified settings for ADC of Cooler Click driver.
 */
#define COOLER_TEMPERATURE_SENS              0.03125f
#define COOLER_SENSOR_VTG_SENS               0.15625f

/**
 * @brief Cooler ADC setting.
 * @details Specified settings for ADC of Cooler Click driver.
 */
#define COOLER_ADC_RESOLUTION                0x0FFFu
#define COOLER_VREF_3V3                      3.3f
#define COOLER_VREF_5V                       5.0f

/**
 * @brief Cooler device address setting.
 * @details Specified setting for device slave address selection of
 * Cooler Click driver.
 */
#define COOLER_SET_DEV_ADDR_0                0x40
#define COOLER_SET_DEV_ADDR_1                0x41
#define COOLER_SET_DEV_ADDR_2                0x44
#define COOLER_SET_DEV_ADDR_3                0x45

/*! @} */ // cooler_set

/**
 * @defgroup cooler_map Cooler MikroBUS Map
 * @brief MikroBUS pin mapping of Cooler Click driver.
 */

/**
 * @addtogroup cooler_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Cooler Click to the selected MikroBUS.
 */
#define COOLER_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // cooler_map
/*! @} */ // cooler

/**
 * @brief Cooler Click driver selector.
 * @details Selects target driver interface of Cooler Click driver.
 */
typedef enum
{
    COOLER_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    COOLER_DRV_SEL_I2C        /**< I2C driver descriptor. */

} cooler_drv_t;

/**
 * @brief Cooler Click context object.
 * @details Context object definition of Cooler Click driver.
 */
typedef struct
{
    digital_out_t in2;      /**< Output 2 control pin. */
    digital_out_t in1;      /**< Output 1 control pin. */

    digital_in_t alr;       /**< Alert pin. */

    analog_in_t  adc;       /**< ADC module object. */
    i2c_master_t i2c;       /**< I2C driver object. */

    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    float   vref;           /**< ADC reference voltage. */

} cooler_t;

/**
 * @brief Cooler Click configuration object.
 * @details Configuration object definition of Cooler Click driver.
 */
typedef struct
{
    pin_name_t an;     /**< Analog pin descriptor. */
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t in2;    /**< Output 2 control pin. */
    pin_name_t in1;    /**< Output 1 control pin. */
    pin_name_t alr;    /**< Alert pin. */

    analog_in_resolution_t resolution;     /**< ADC resolution. */
    float                  vref;           /**< ADC reference voltage. */

    uint32_t               i2c_speed;      /**< I2C serial speed. */
    uint8_t                i2c_address;    /**< I2C slave address. */

} cooler_cfg_t;

/**
 * @brief Cooler Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COOLER_OK = 0,
    COOLER_ERROR = -1

} cooler_return_value_t;

/**
 * @brief Cooler Click cooler states selection.
 * @details Predefined enum values for cooler states selection.
 */
typedef enum
{
    COOLER_ENABLE = 0,
    COOLER_DISABLE
    
} cooler_out_state_t;

/*!
 * @addtogroup cooler Cooler Click Driver
 * @brief API for configuring and manipulating Cooler Click driver.
 * @{
 */

/**
 * @brief Cooler configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #cooler_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void cooler_cfg_setup ( cooler_cfg_t *cfg );


/**
 * @brief Cooler initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #cooler_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_init ( cooler_t *ctx, cooler_cfg_t *cfg );

/**
 * @brief Cooler default configuration function.
 * @details This function executes a default configuration of Cooler
 * click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t cooler_default_cfg ( cooler_t *ctx );

/**
 * @brief Cooler data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_generic_write ( cooler_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Cooler data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_generic_read ( cooler_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Cooler 16-bit data writing function.
 * @details This function writes a 16-bit data to the selected register
 * of the TMP007 Infrared Thermopile Sensor with Integrated Math Engine
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_data_write ( cooler_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Cooler 16-bit data reading function.
 * @details This function reads a 16-bit data from the selected register 
 * of the TMP007 Infrared Thermopile Sensor with Integrated Math Engine
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_data_read ( cooler_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Cooler get device ID function.
 * @details This function reads a device ID value 
 * of the TMP007 Infrared Thermopile Sensor with Integrated Math Engine
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_get_device_id ( cooler_t *ctx, uint16_t *device_id );

/**
 * @brief Cooler get sensor voltage result function.
 * @details This function reads the sensor voltage result
 * of the TMP007 Infrared Thermopile Sensor with Integrated Math Engine
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[out] voltage : Sensor voltage result [+-5.12mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_sensor_voltage ( cooler_t *ctx, float *voltage );

/**
 * @brief Cooler get object temperature function.
 * @details This function reads the object's temperature data in degrees Celsius
 * of the TMP007 Infrared Thermopile Sensor with Integrated Math Engine
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[out] temperature : Temperature (degrees Celsius).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_get_object_temperature ( cooler_t *ctx, float *temperature );

/**
 * @brief Cooler fault indication function.
 * @details This function reads the state of the ALR (INT) pin of Cooler
 * click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t cooler_get_alert ( cooler_t *ctx );

/**
 * @brief Cooler read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_read_raw_adc ( cooler_t *ctx, uint16_t *raw_adc );

/**
 * @brief Cooler read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t cooler_read_voltage ( cooler_t *ctx, float *voltage );

/**
 * @brief Cooler set vref function.
 * @details This function sets the voltage reference for Cooler click driver.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b cooler_init is 3.3V.
 */
err_t cooler_set_vref ( cooler_t *ctx, float vref );

/**
 * @brief Cooler set IN1 pin state function.
 * @details This function sets the IN1 (PWM) pin on the high level 
 * of the DRV8213 4-A Brushed DC Motor Driver with Integrated Current Sense, 
 * Current Regulation and Stall Detection
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void cooler_set_in1_pin ( cooler_t *ctx );

/**
 * @brief Cooler IN1 pin clearing function.
 * @details This function clears the IN1 (PWM) pin on the low level
 * of the DRV8213 4-A Brushed DC Motor Driver with Integrated Current Sense, 
 * Current Regulation and Stall Detection
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void cooler_clear_in1_pin ( cooler_t *ctx );

/**
 * @brief Cooler set IN2 pin state function.
 * @details This function sets the IN2 (RST) pin on the high level 
 * of the DRV8213 4-A Brushed DC Motor Driver with Integrated Current Sense, 
 * Current Regulation and Stall Detection
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void cooler_set_in2_pin ( cooler_t *ctx );

/**
 * @brief Cooler IN2 pin clearing function.
 * @details This function clears the IN2 (RST) pin on the low level
 * of the DRV8213 4-A Brushed DC Motor Driver with Integrated Current Sense, 
 * Current Regulation and Stall Detection
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void cooler_clear_in2_pin ( cooler_t *ctx );

/**
 * @brief Cooler set output function.
 * @details This function controls the operation of the cooler - on/off
 * of the DRV8213 4-A Brushed DC Motor Driver with Integrated Current Sense, 
 * Current Regulation and Stall Detection
 * on the Cooler click board.
 * @param[in] ctx : Click context object.
 * See #cooler_t object definition for detailed explanation.
 * @param[in] out_state : Motor states selection.
 * See #cooler_out_state_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cooler_set_out_state ( cooler_t *ctx, cooler_out_state_t out_state );

#ifdef __cplusplus
}
#endif
#endif // COOLER_H

/*! @} */ // cooler

// ------------------------------------------------------------------------ END
