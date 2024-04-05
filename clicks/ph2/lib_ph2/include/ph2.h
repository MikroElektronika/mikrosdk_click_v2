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
 * @file ph2.h
 * @brief This file contains API for pH 2 Click Driver.
 */

#ifndef PH2_H
#define PH2_H

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
#include "drv_one_wire.h"

/*!
 * @addtogroup ph2 pH 2 Click Driver
 * @brief API for configuring and manipulating pH 2 Click driver.
 * @{
 */

/**
 * @defgroup ph2_cmd pH 2 Commands List
 * @brief List of commands of pH 2 Click driver.
 */

/**
 * @addtogroup ph2_cmd
 * @{
 */

/**
 * @brief pH 2 DS18B20 commands list.
 * @details Specified commands list for setting DS18B20 of pH 2 Click driver.
 */
#define PH2_CMD_CONVERT_TEMPERATURE     0x44
#define PH2_CMD_WRITE_SCRATCHPAD        0x4E
#define PH2_CMD_READ_SCRATCHPAD         0xBE
#define PH2_CMD_COPY_SCRATCHPAD         0x48
#define PH2_CMD_RECALL_SCRATCHPAD       0xB8
#define PH2_CMD_READ_POWER_SUPPLY       0xB4

/*! @} */ // ph2_cmd

/**
 * @defgroup ph2_set pH 2 Registers Settings
 * @brief Settings for registers of pH 2 Click driver.
 */

/**
 * @addtogroup ph2_set
 * @{
 */

/**
 * @brief pH 2 description setting.
 * @details Specified setting for description of pH 2 Click driver.
 */
#define PH2_PH_CALCULATION_COEF     0.18

#define PH2_CONFIG_ADDRESS          0x10
/**
 * @brief pH 2 ADC setting.
 * @details Specified settings for ADC of pH 2 Click driver.
 */
#define PH2_ADC_RESOLUTION          0x0FFF
#define PH2_VREF_3V3                3.3
#define PH2_VREF_5V                 5.0

/**
 * @brief pH 2 device address setting.
 * @details Specified setting for device slave address selection of
 * pH 2 Click driver.
 */
#define PH2_SET_DEV_ADDR            0x4D

/**
 * @brief pH 2 DS18B20 family code value.
 * @details Specified family code value of DS18B20 of pH 2 2 Click driver.
 */
#define PH2_FAMILY_CODE             0x28

/**
 * @brief pH 2 config register settings.
 * @details Specified config register settings of pH 2 Click driver.
 */

#define PH2_CONFIG_RESOLUTION_9BIT      0x00
#define PH2_CONFIG_RESOLUTION_10BIT     0x20
#define PH2_CONFIG_RESOLUTION_11BIT     0x40
#define PH2_CONFIG_RESOLUTION_12BIT     0x60
#define PH2_CONFIG_RESOLUTION_BIT_MASK  0x60
#define PH2_CONFIG_RESERVED_BITS        0x10

/**
 * @brief pH 2 temperature calculation values.
 * @details Specified temperature calculation values of pH 2 Click driver.
 */
#define PH2_DATA_RESOLUTION             0.0625

/**
 * @brief pH 2 default config values.
 * @details Specified default config values of pH 2 Click driver.
 */
#define PH2_DEFAULT_ADDRESS             PH2_CONFIG_ADDRESS
#define PH2_DEFAULT_RESOLUTION          PH2_CONFIG_RESOLUTION_12BIT
#define PH2_DEFAULT_TEMP_HIGH_ALARM     0xFF
#define PH2_DEFAULT_TEMP_LOW_ALARM      0x00

/*! @} */ // ph2_set

/**
 * @defgroup ph2_map pH 2 MikroBUS Map
 * @brief MikroBUS pin mapping of pH 2 Click driver.
 */

/**
 * @addtogroup ph2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of pH 2 Click to the selected MikroBUS.
 */
#define PH2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dq = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.st1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.st2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ph2_map
/*! @} */ // ph2

/**
 * @brief pH 2 Click driver selector.
 * @details Selects target driver interface of pH 2 Click driver.
 */
typedef enum
{
    PH2_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    PH2_DRV_SEL_I2C        /**< I2C driver descriptor. */

} ph2_drv_t;

/**
 * @brief pH 2 Click context object.
 * @details Context object definition of pH 2 Click driver.
 */
typedef struct
{
    digital_out_t st1;              /**< Status 1 pin. */
    digital_out_t st2;              /**< Status 2 pin. */

    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */
    one_wire_t ow;                  /**< One Wire driver object. */
    
    float pH_val;
    float pH_vol;

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t config;                     /**< Device configuration register setting. */
    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    float        vref;              /**< ADC reference voltage. */
    ph2_drv_t drv_sel;              /**< Master driver interface selector. */

} ph2_t;

/**
 * @brief pH 2 Click configuration object.
 * @details Configuration object definition of pH 2 Click driver.
 */
typedef struct
{
    pin_name_t an;              /**< Analog pin descriptor. */
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t dq;              /**< Thermpo data pin. */
    pin_name_t st1;             /**< Status 1 pin. */
    pin_name_t st2;             /**< Status 2 pin. */

    analog_in_resolution_t resolution;              /**< ADC resolution. */
    float                  vref;                    /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;               /**< I2C serial speed. */
    uint8_t                i2c_address;             /**< I2C slave address. */
    
    ph2_drv_t drv_sel;                /**< Master driver interface selector. */

} ph2_cfg_t;

/**
 * @brief pH 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PH2_OK = 0,
    PH2_ERROR = -1

} ph2_return_value_t;

/*!
 * @addtogroup ph2 pH 2 Click Driver
 * @brief API for configuring and manipulating pH 2 Click driver.
 * @{
 */

/**
 * @brief pH 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ph2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ph2_cfg_setup ( ph2_cfg_t *cfg );

/**
 * @brief pH 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ph2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ph2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ph2_drv_interface_selection ( ph2_cfg_t *cfg, ph2_drv_t drv_sel );

/**
 * @brief pH 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ph2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_init ( ph2_t *ctx, ph2_cfg_t *cfg );

/**
 * @brief pH 2 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_read_raw_adc ( ph2_t *ctx, uint16_t *raw_adc );

/**
 * @brief pH 2 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t ph2_read_voltage ( ph2_t *ctx, float *voltage );

/**
 * @brief pH 2 set vref function.
 * @details This function sets the voltage reference for pH 2 click driver.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b ph2_init is 3.3V.
 */
err_t ph2_set_vref ( ph2_t *ctx, float vref );

/**
 * @brief Ph 2 calibrate function.
 * @details This function is performing calibration of Ph 2 click driver 
 * with known pH value substance.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[out] pH_value : pH value of the substance where calibration is performed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_calibrate ( ph2_t *ctx, float pH_value );

/**
 * @brief Ph 2 calculate pH value function.
 * @details This function is reading pH value wof substance where pH probe is placed.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[out] pH_value : pH value of the substance.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function calculates the pH value with the assumption that the temperature of the 
 * substance is 25 deg Celsius.
 */
err_t ph2_calculate_ph ( ph2_t *ctx, float *pH_value );

/**
 * @brief Ph 2 calibrate offset function.
 * @details This function is used to calibrate offset of Ph 2 click driver.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return Nothing.
 * @note Disconnect the probe and short-circuit the BNC connector in order to set 
 * the reference voltage. Adjust the potentiometer until the LEDs stop blinking or until 
 * the voltage of the OUT pin is exactly at half the value of the selected VCC voltage. 
 * If you are using LEDs for calibration, turn the potentiometer clockwise when 
 * STAT1 LED is blinking and counter-clockwise when STAT2 LED is blinking.
 */
void ph2_calibrate_offset ( ph2_t *ctx );

/**
 * @brief Ph 2 enable LED STAT1 function.
 * @details This function is used turn on STAT1 LED of Ph 2 click driver.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ph2_enable_st1 ( ph2_t *ctx );

/**
 * @brief Ph 2 disable LED STAT1 function.
 * @details This function is used turn off STAT1 LED of Ph 2 click driver.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ph2_disable_st1 ( ph2_t *ctx );

/**
 * @brief Ph 2 enable LED STAT2 function.
 * @details This function is used turn on STAT2 LED of Ph 2 click driver.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ph2_enable_st2 ( ph2_t *ctx );

/**
 * @brief Ph 2 disable LED STAT2 function.
 * @details This function is used turn off STAT2 LED of Ph 2 click driver.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ph2_disable_st2 ( ph2_t *ctx );

/**
 * @brief pH 2 DS18B20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for DS18B20 sensor.
 * @param[out] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ph2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_ds18b20_init ( ph2_t *ctx, ph2_cfg_t *cfg );

/**
 * @brief pH 2 DS18B20 check communication function.
 * @details This function checks the communication by reading the ROM address 
 * as well as verifying family code and Maxim CRC 8.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_ds18b20_check_communication ( ph2_t *ctx );

/**
 * @brief pH 2 DS18B20 select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the @b ctx->address.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_ds18b20_select_device ( ph2_t *ctx );

/**
 * @brief pH 2 DS18B20 read scratchpad function.
 * @details This function reads a desired number of scratchpad bytes using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[out] scratchpad : Output read scratchpad.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_ds18b20_read_scratchpad ( ph2_t *ctx, uint8_t *scratchpad );

/**
 * @brief pH 2 DS18B20 write scratchpad function.
 * @details This function writes the temperature thresholds and configuration byte to the scratchpad.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[in] temp_high : Temperature high limit.
 * @param[in] temp_low : Temperature low limit.
 * @param[in] config : Configuration byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_ds18b20_write_scratchpad ( ph2_t *ctx, uint8_t temp_high, uint8_t temp_low, uint8_t config );

/**
 * @brief pH 2 DS18B20 default configuration function.
 * @details This function executes a default configuration of pH 2 DS18B20 sensor.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ph2_ds18b20_default_cfg ( ph2_t *ctx );

/**
 * @brief pH 2 DS18B20 start measurement function.
 * @details This function starts the measurement by sending an appropriate command for that.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_ds18b20_start_measurement ( ph2_t *ctx );

/**
 * @brief pH 2 DS18B20 read temperature function.
 * @details This function reads the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #ph2_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ph2_ds18b20_read_temperature ( ph2_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // PH2_H

/*! @} */ // ph2

// ------------------------------------------------------------------------ END
