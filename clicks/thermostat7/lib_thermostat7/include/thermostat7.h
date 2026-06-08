/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file thermostat7.h
 * @brief This file contains API for Thermostat 7 Click Driver.
 */

#ifndef THERMOSTAT7_H
#define THERMOSTAT7_H

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
 * @addtogroup thermostat7 Thermostat 7 Click Driver
 * @brief API for configuring and manipulating Thermostat 7 Click driver.
 * @{
 */

/**
 * @defgroup thermostat7_reg Thermostat 7 Registers List
 * @brief List of registers of Thermostat 7 Click driver.
 */

/**
 * @addtogroup thermostat7_reg
 * @{
 */

/**
 * @brief Thermostat 7 register list.
 * @details Specified register list of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_REG_CAPABILITY          0x00
#define THERMOSTAT7_REG_CONFIGURATION       0x01
#define THERMOSTAT7_REG_HIGH_LIMIT          0x02
#define THERMOSTAT7_REG_LOW_LIMIT           0x03
#define THERMOSTAT7_REG_CRITICAL_LIMIT      0x04
#define THERMOSTAT7_REG_TEMPERATURE         0x05
#define THERMOSTAT7_REG_MANUFACTURER_ID     0x06
#define THERMOSTAT7_REG_DEVICE_ID           0x07

/*! @} */ // thermostat7_reg

/**
 * @defgroup thermostat7_set Thermostat 7 Registers Settings
 * @brief Settings for registers of Thermostat 7 Click driver.
 */

/**
 * @addtogroup thermostat7_set
 * @{
 */

/**
 * @brief Thermostat 7 CONFIGURATION register setting.
 * @details Specified setting for CONFIGURATION register of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_CFG_HYST_DISABLE        0x0000
#define THERMOSTAT7_CFG_HYST_1_5            0x0200 
#define THERMOSTAT7_CFG_HYST_3              0x0400  
#define THERMOSTAT7_CFG_HYST_6              0x0600  
#define THERMOSTAT7_CFG_SHDN                0x0100  
#define THERMOSTAT7_CFG_TCRIT_LOCK          0x0080  
#define THERMOSTAT7_CFG_ALARM_LOCK          0x0040  
#define THERMOSTAT7_CFG_CLEAR_INT           0x0020  
#define THERMOSTAT7_CFG_EVENT_CTRL_EN       0x0008  
#define THERMOSTAT7_CFG_TCRIT_ONLY          0x0004  
#define THERMOSTAT7_CFG_EVENT_POL_HIGH      0x0002  
#define THERMOSTAT7_CFG_EVENT_MODE_INT      0x0001  

/**
 * @brief Thermostat 7 TEMPERATURE DATA register setting.
 * @details Specified setting for TEMPERATURE DATA register of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_TDR_TCRIT_FLAG          0x8000  
#define THERMOSTAT7_TDR_HIGH_FLAG           0x4000  
#define THERMOSTAT7_TDR_LOW_FLAG            0x2000  
#define THERMOSTAT7_TDR_SIGN_BIT            0x1000  
#define THERMOSTAT7_TDR_DATA_MASK           0x1FFF  

/**
 * @brief Thermostat 7 MANUFACTURER ID register setting.
 * @details Specified setting for MANUFACTURER ID register of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_MANUFACTURER_ID         0x1B09

/**
 * @brief Thermostat 7 DEVICE ID register setting.
 * @details Specified setting for DEVICE ID register of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_DEVICE_ID               0x2230

/**
 * @brief Thermostat 7 alarms setting.
 * @details Specified setting for alarms of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_ALARM_NONE              0x00
#define THERMOSTAT7_ALARM_LOW               0x01
#define THERMOSTAT7_ALARM_HIGH              0x02
#define THERMOSTAT7_ALARM_TCRIT             0x04

/**
 * @brief Thermostat 7 resolution setting.
 * @details Specified setting for resolution of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_TEMP_RESOLUTION         0.0625f  
#define THERMOSTAT7_LIMIT_RESOLUTION        0.25f    

/**
 * @brief Thermostat 7 limits setting.
 * @details Specified setting for limits of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_DEFAULT_TEMP_HIGH       30.0f    
#define THERMOSTAT7_DEFAULT_TEMP_LOW        0.0f     
#define THERMOSTAT7_DEFAULT_TEMP_CRITICAL   35.0f    

/**
 * @brief Thermostat 7 limit registers setting.
 * @details Specified setting for limit registers of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_LIMIT_REG_SHIFT         2
#define THERMOSTAT7_LIMIT_REG_MASK          0x1FFC

/**
 * @brief Thermostat 7 sign extension setting.
 * @details Specified setting for sign extension of Thermostat 7 Click driver.
 */
#define THERMOSTAT7_TEMP_SIGN_EXTEND        0xE000

/**
 * @brief Thermostat 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermostat 7 Click driver.
 */
#define THERMOSTAT7_DEVICE_ADDRESS          0x1F

/*! @} */ // thermostat7_set

/**
 * @defgroup thermostat7_map Thermostat 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermostat 7 Click driver.
 */

/**
 * @addtogroup thermostat7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermostat 7 Click to the selected MikroBUS.
 */
#define THERMOSTAT7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \

/*! @} */ // thermostat7_map
/*! @} */ // thermostat7

/**
 * @brief Thermostat 7 Click context object.
 * @details Context object definition of Thermostat 7 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} thermostat7_t;

/**
 * @brief Thermostat 7 Click configuration object.
 * @details Configuration object definition of Thermostat 7 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} thermostat7_cfg_t;

/**
 * @brief Thermostat 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMOSTAT7_OK = 0,
    THERMOSTAT7_ERROR = -1

} thermostat7_return_value_t;

/*!
 * @addtogroup thermostat7 Thermostat 7 Click Driver
 * @brief API for configuring and manipulating Thermostat 7 Click driver.
 * @{
 */

/**
 * @brief Thermostat 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermostat7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermostat7_cfg_setup ( thermostat7_cfg_t *cfg );

/**
 * @brief Thermostat 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermostat7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_init ( thermostat7_t *ctx, thermostat7_cfg_t *cfg );

/**
 * @brief Thermostat 7 default configuration function.
 * @details This function executes a default configuration of Thermostat 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermostat7_default_cfg ( thermostat7_t *ctx );

/**
 * @brief Thermostat 7 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_write_reg ( thermostat7_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Thermostat 7 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_write_regs ( thermostat7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Thermostat 7 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_read_reg ( thermostat7_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Thermostat 7 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_read_regs ( thermostat7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Thermostat 7 check communication function.
 * @details This function checks communication by reading the manufacturer ID.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_check_communication ( thermostat7_t *ctx );

/**
 * @brief Thermostat 7 set high limit function.
 * @details This function sets the high alarm temperature limit.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[in] temperature_limit : Temperature high limit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_set_high_limit ( thermostat7_t *ctx, float temperature_limit );

/**
 * @brief Thermostat 7 set low limit function.
 * @details This function sets the low alarm temperature limit.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[in] temperature_limit : Temperature low limit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_set_low_limit ( thermostat7_t *ctx, float temperature_limit );

/**
 * @brief Thermostat 7 set critical limit function.
 * @details This function sets the critical alarm temperature limit.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[in] temperature_limit : Temperature critical limit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_set_critical_limit ( thermostat7_t *ctx, float temperature_limit );

/**
 * @brief Thermostat 7 read temperature function.
 * @details This function reads the temperature value in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to stored temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_read_temperature ( thermostat7_t *ctx, float *temperature );

/**
 * @brief Thermostat 7 read alarm status function.
 * @details This function reads the current alarm status by reading
 * the temperature data register.
 * @param[in] ctx : Click context object.
 * See #thermostat7_t object definition for detailed explanation.
 * @param[out] status : Pointer to stored alarm status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat7_read_alarm_status ( thermostat7_t *ctx, uint8_t *status );

#ifdef __cplusplus
}
#endif
#endif // THERMOSTAT7_H

/*! @} */ // thermostat7

// ------------------------------------------------------------------------ END
