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
 * @file powermonitor.h
 * @brief This file contains API for Power Monitor Click Driver.
 */

#ifndef POWERMONITOR_H
#define POWERMONITOR_H

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
 * @addtogroup powermonitor Power Monitor Click Driver
 * @brief API for configuring and manipulating Power Monitor Click driver.
 * @{
 */

/**
 * @defgroup powermonitor_reg Power Monitor Registers List
 * @brief List of registers of Power Monitor Click driver.
 */

/**
 * @addtogroup powermonitor_reg
 * @{
 */

/**
 * @brief Power Monitor description register.
 * @details Specified register for description of Power Monitor Click driver.
 */
#define POWERMONITOR_REG_CONFIG                    0x00
#define POWERMONITOR_REG_ADCCONFIG                 0x01
#define POWERMONITOR_REG_SHUNT_CAL                 0x02
#define POWERMONITOR_REG_SHUNT_TEMPCO              0x03
#define POWERMONITOR_REG_VSHUNT                    0x04
#define POWERMONITOR_REG_VBUS                      0x05
#define POWERMONITOR_REG_DIETEMP                   0x06
#define POWERMONITOR_REG_CURRENT                   0x07
#define POWERMONITOR_REG_POWER                     0x08
#define POWERMONITOR_REG_ENERGY                    0x09
#define POWERMONITOR_REG_CHARGE                    0x0A
#define POWERMONITOR_REG_DIAG_ALR                  0x0B
#define POWERMONITOR_REG_SOVL                      0x0C
#define POWERMONITOR_REG_SUVL                      0x0D
#define POWERMONITOR_REG_BOVL                      0x0E
#define POWERMONITOR_REG_BUVL                      0x0F
#define POWERMONITOR_REG_TEMP_LIMIT                0x10
#define POWERMONITOR_REG_PWR_LIMIT                 0x11
#define POWERMONITOR_REG_MANUFACTURER_ID           0x3E
#define POWERMONITOR_REG_DEVICE_ID                 0x3F

/*! @} */ // powermonitor_reg

/**
 * @defgroup powermonitor_set Power Monitor Registers Settings
 * @brief Settings for registers of Power Monitor Click driver.
 */

/**
 * @addtogroup powermonitor_set
 * @{
 */

/**
 * @brief Power Monitor description setting.
 * @details Specified setting for description of Power Monitor Click driver.
 */
#define POWERMONITOR_RST_RESET_BIT                           0x80
#define POWERMONITOR_RSTACC_NORMAL_OPERATION                 0x00
#define POWERMONITOR_RSTACC_CLEARS_ENERGY_CHARGE_REG         0x01
#define POWERMONITOR_CONVDLY_0_s                             0x00
#define POWERMONITOR_TEMPCOMP_DISABLED                       0x00
#define POWERMONITOR_TEMPCOMP_ENABLED                        0x01
#define POWERMONITOR_ADCRANGE_163_84_mV                      0x00
#define POWERMONITOR_ADCRANGE_40_96_mV                       0x01
#define POWERMONITOR_MODE_SINGLE_SHOT_SHUTDOWN               0x00
#define POWERMONITOR_MODE_SINGLE_SHOT_BUS_VOLTAGE            0x01
    
#define POWERMONITOR_MODE_SINGLE_SHOT_BUS_VTG                0x01
#define POWERMONITOR_MODE_SINGLE_SHOT_SHUNT_VTG              0x02
#define POWERMONITOR_MODE_SINGLE_SHOT_SHUNT_BUS_VTG          0x03
#define POWERMONITOR_MODE_SINGLE_TEMPERATURE                 0x04
#define POWERMONITOR_MODE_SINGLE_SHOT_TEMP_BUS_VTG           0x05
#define POWERMONITOR_MODE_SINGLE_SHOT_TEMP_SHUNT_VTG         0x06
#define POWERMONITOR_MODE_SINGLE_SHOT_TEMP_SHUNT_BUS_VTG     0x07
#define POWERMONITOR_MODE_CONTINUOUS_SHOT_BUS_VOLTAGE        0x08
#define POWERMONITOR_MODE_CONTINUOUS_SHOT_BUS_VTG            0x09
#define POWERMONITOR_MODE_CONTINUOUS_SHOT_SHUNT_VTG          0x0A
#define POWERMONITOR_MODE_CONTINUOUS_SHOT_SHUNT_BUS_VTG      0x0B
#define POWERMONITOR_MODE_CONTINUOUS_TEMPERATURE             0x0C
#define POWERMONITOR_MODE_CONTINUOUS_SHOT_TEMP_BUS_VTG       0x0D
#define POWERMONITOR_MODE_CONTINUOUS_SHOT_TEMP_SHUNT_VTG     0x0E
#define POWERMONITOR_MODE_CONTINUOUS_SHOT_TEMP_SHUNT_BUS_VTG 0x0F
    
#define POWERMONITOR_VBUSCT_CONVERSION_TIME_50_nS            0x00
#define POWERMONITOR_VBUSCT_CONVERSION_TIME_84_nS            0x01
#define POWERMONITOR_VBUSCT_CONVERSION_TIME_150_nS           0x02
#define POWERMONITOR_VBUSCT_CONVERSION_TIME_280_nS           0x03
#define POWERMONITOR_VBUSCT_CONVERSION_TIME_540_nS           0x04
#define POWERMONITOR_VBUSCT_CONVERSION_TIME_1052_nS          0x05
#define POWERMONITOR_VBUSCT_CONVERSION_TIME_2074_nS          0x06
#define POWERMONITOR_VBUSCT_CONVERSION_TIME_4120_nS          0x07
    
#define POWERMONITOR_VSHCT_CONVERSION_TIME_50_nS             0x00
#define POWERMONITOR_VSHCT_CONVERSION_TIME_84_nS             0x01
#define POWERMONITOR_VSHCT_CONVERSION_TIME_150_nS            0x02
#define POWERMONITOR_VSHCT_CONVERSION_TIME_280_nS            0x03
#define POWERMONITOR_VSHCT_CONVERSION_TIME_540_nS            0x04
#define POWERMONITOR_VSHCT_CONVERSION_TIME_1052_nS           0x05
#define POWERMONITOR_VSHCT_CONVERSION_TIME_2074_nS           0x06
#define POWERMONITOR_VSHCT_CONVERSION_TIME_4120_nS           0x07
    
#define POWERMONITOR_VTCT_CONVERSION_TIME_50_nS              0x00
#define POWERMONITOR_VTCT_CONVERSION_TIME_84_nS              0x01
#define POWERMONITOR_VTCT_CONVERSION_TIME_150_nS             0x02
#define POWERMONITOR_VTCT_CONVERSION_TIME_280_nS             0x03
#define POWERMONITOR_VTCT_CONVERSION_TIME_540_nS             0x04
#define POWERMONITOR_VTCT_CONVERSION_TIME_1052_nS            0x05
#define POWERMONITOR_VTCT_CONVERSION_TIME_2074_nS            0x06
#define POWERMONITOR_VTCT_CONVERSION_TIME_4120_nS            0x07

#define POWERMONITOR_AVG_AVERAGING_COUNT_1                   0x00
#define POWERMONITOR_AVG_AVERAGING_COUNT_4                   0x01
#define POWERMONITOR_AVG_AVERAGING_COUNT_16                  0x02
#define POWERMONITOR_AVG_AVERAGING_COUNT_64                  0x03
#define POWERMONITOR_AVG_AVERAGING_COUNT_128                 0x04
#define POWERMONITOR_AVG_AVERAGING_COUNT_256                 0x05
#define POWERMONITOR_AVG_AVERAGING_COUNT_512                 0x06
#define POWERMONITOR_AVG_AVERAGING_COUNT_1024                0x07

/**
 * @brief Power Monitor device address setting.
 * @details Specified setting for device slave address selection of
 * Power Monitor Click driver.
 */
#define POWERMONITOR_SET_DEV_ADDR_GND_GND            0x40
#define POWERMONITOR_SET_DEV_ADDR_GND_VS             0x41
#define POWERMONITOR_SET_DEV_ADDR_GND_SDA            0x42
#define POWERMONITOR_SET_DEV_ADDR_GND_SCL            0x43
#define POWERMONITOR_SET_DEV_ADDR_VS_GND             0x44
#define POWERMONITOR_SET_DEV_ADDR_VS_VS              0x45
#define POWERMONITOR_SET_DEV_ADDR_VS_SDA             0x46
#define POWERMONITOR_SET_DEV_ADDR_VS_SCL             0x47
#define POWERMONITOR_SET_DEV_ADDR_SDA_GND            0x48
#define POWERMONITOR_SET_DEV_ADDR_SDA_VS             0x49
#define POWERMONITOR_SET_DEV_ADDR_SDA_SDA            0x4A
#define POWERMONITOR_SET_DEV_ADDR_SDA_SCL            0x4B
#define POWERMONITOR_SET_DEV_ADDR_SCL_GND            0x4C
#define POWERMONITOR_SET_DEV_ADDR_SCL_VS             0x4D
#define POWERMONITOR_SET_DEV_ADDR_SCL_SDA            0x4E
#define POWERMONITOR_SET_DEV_ADDR_SCL_SCL            0x4F

/*! @} */ // powermonitor_set

/**
 * @defgroup powermonitor_map Power Monitor MikroBUS Map
 * @brief MikroBUS pin mapping of Power Monitor Click driver.
 */

/**
 * @addtogroup powermonitor_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Power Monitor Click to the selected MikroBUS.
 */
#define POWERMONITOR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // powermonitor_map
/*! @} */ // powermonitor

/**
 * @brief Power Monitor Click context object.
 * @details Context object definition of Power Monitor Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  alr;       /**< Alert pin. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */
    
    float shunt;

} powermonitor_t;

/**
 * @brief Power Monitor Click configuration object.
 * @details Configuration object definition of Power Monitor Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  alr;        /**< Alert pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} powermonitor_cfg_t;

/**
 * @brief Power Monitor Click device settings object.
 * @details Settings object definition of Power Monitor Click driver.
 */
typedef struct
{
    uint8_t rstacc;
    uint8_t convdly;
    uint8_t tempcomp;
    uint8_t adcrange;

} powermonitor_dev_cfg_t;

/**
 * @brief Power Monitor Click ADC configuration object.
 * @details ADC configuration object definition of Power Monitor Click driver.
 */
typedef struct
{
    uint8_t mode;
    uint8_t vbusct;
    uint8_t vshct;
    uint8_t vtct;
    uint8_t avg;

} powermonitor_adc_cfg_t;

/**
 * @brief Power Monitor Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   POWERMONITOR_OK = 0,
   POWERMONITOR_ERROR = -1

} powermonitor_return_value_t;

/*!
 * @addtogroup powermonitor Power Monitor Click Driver
 * @brief API for configuring and manipulating Power Monitor Click driver.
 * @{
 */

/**
 * @brief Power Monitor configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #powermonitor_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void powermonitor_cfg_setup ( powermonitor_cfg_t *cfg );

/**
 * @brief Power Monitor initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #powermonitor_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_init ( powermonitor_t *ctx, powermonitor_cfg_t *cfg );

/**
 * @brief Power Monitor default configuration function.
 * @details This function executes a default configuration of Power Monitor
 * Click board.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t powermonitor_default_cfg ( powermonitor_t *ctx );

/**
 * @brief Power Monitor I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_generic_write ( powermonitor_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Power Monitor I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_generic_read ( powermonitor_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Power Monitor software reset function.
 * @details This function executes a software reset 
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_soft_reset ( powermonitor_t *ctx );

/**
 * @brief Power Monitor set configuration function.
 * @details This function performs configuration 
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] cfg_data : Settings object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_set_configuration ( powermonitor_t *ctx, powermonitor_dev_cfg_t cfg_data );

/**
 * @brief Power Monitor get configuration function.
 * @details This function get configuration 
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] cfg_data : Settings object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_configuration ( powermonitor_t *ctx, powermonitor_dev_cfg_t *cfg_data );

/**
 * @brief Power Monitor set ADC configuration function.
 * @details This function performs ADC configuration 
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] adc_cfg : ADC configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_set_adc_config ( powermonitor_t *ctx, powermonitor_adc_cfg_t adc_cfg );

/**
 * @brief Power Monitor get ADC configuration function.
 * @details This function get ADC configuration 
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] adc_cfg : ADC configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_adc_configu ( powermonitor_t *ctx, powermonitor_adc_cfg_t *adc_cfg );

/**
 * @brief Power Monitor set bus overvoltage threshold function.
 * @details This function sets the bus overvoltage threshold for comparison 
 * of the value to detect Bus Overvoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] bovl : Overvoltage threshold for comparison ( 0 mV - 102400 mV) .
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_set_bus_overvoltage_threshold ( powermonitor_t *ctx, float bovl );

/**
 * @brief Power Monitor set bus undervoltage threshold function.
 * @details This function sets the bus undervoltage threshold for comparison 
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] buvl : Undervoltage threshold for comparison ( 0 mV - 102400 mV) .
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_set_bus_undervoltage_threshold ( powermonitor_t *ctx, float buvl );

/**
 * @brief Power Monitor set shunt overvoltage threshold function.
 * @details This function sets the shunt overvoltage threshold for comparison 
 * of the value to detect Bus Overvoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] sovl : Overvoltage threshold for comparison 
 *  ( ADCRANGE = 0 : 0 mV - 327.680 mV; ADCRANGE = 1 : 0 mV - 81.920 mV ) .
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_set_shunt_overvoltage_threshold ( powermonitor_t *ctx, float sovl );

/**
 * @brief Power Monitor set shunt undervoltage threshold function.
 * @details This function sets the shunt undervoltage threshold for comparison 
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[in] suvl : Undervoltage threshold for comparison 
 *  ( ADCRANGE = 0 : 0 mV - 327.680 mV; ADCRANGE = 1 : 0 mV - 81.920 mV ) .
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_set_shunt_undervoltage_threshold ( powermonitor_t *ctx, float suvl );

/**
 * @brief Power Monitor get shunt voltage function.
 * @details This function get shunt voltage measurement
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] vshunt : Differential voltage measured ( mV ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_vshunt ( powermonitor_t *ctx, float *vshunt );

/**
 * @brief Power Monitor get bus voltage function.
 * @details This function get bus voltage measurement
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] vbus : Bus voltage output ( mV ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_vbus ( powermonitor_t *ctx, float *vbus );

/**
 * @brief Power Monitor get temperature function.
 * @details This function get temperature measurement
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] temperature : Temperature ( degree Celsius ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_temperature ( powermonitor_t *ctx, float *temperature );

/**
 * @brief Power Monitor get current function.
 * @details This function get and calculate current output 
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] current : Current output ( mA ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_current ( powermonitor_t *ctx, float *current );

/**
 * @brief Power Monitor get power function.
 * @details This function get and calculate power output 
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] power : Power output ( W ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_power ( powermonitor_t *ctx, float *power );

/**
 * @brief Power Monitor get energy data function.
 * @details This function read energy data 
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] energy_data : Pointer to the memory location where the data is stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_energy_data ( powermonitor_t *ctx, uint8_t *energy_data );

/**
 * @brief Power Monitor get energy function.
 * @details This function get and calculate energy output 
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] energy : Energy output ( J ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_energy ( powermonitor_t *ctx, float *energy );

/**
 * @brief Power Monitor get device ID function.
 * @details This function get device ID 
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @param[out] manufacturer_id : Reads back TI in ASCII.
 * @param[out] die_id : Stores the device identification bits.
 * @param[out] rev_id : Device revision identification.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_id ( powermonitor_t *ctx, uint8_t *manufacturer_id, uint16_t *die_id, uint8_t *rev_id );

/**
 * @brief Power Monitor get alert function.
 * @details This function get alert state 
 * of the value to detect Bus Undervoltage
 * of the INA228 85-V, 20-Bit, Ultra-Precise Power/Energy/Charge Monitor 
 * on the Power Monitor Click board™.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @return @li @c 0 - Alert state active,
 *         @li @c 1 - Alert state inactive.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t powermonitor_get_alert ( powermonitor_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // POWERMONITOR_H

/*! @} */ // powermonitor

// ------------------------------------------------------------------------ END
