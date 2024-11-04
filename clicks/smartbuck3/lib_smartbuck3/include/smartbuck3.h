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
 * @file smartbuck3.h
 * @brief This file contains API for Smart Buck 3 Click Driver.
 */

#ifndef SMARTBUCK3_H
#define SMARTBUCK3_H

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
 * @addtogroup smartbuck3 Smart Buck 3 Click Driver
 * @brief API for configuring and manipulating Smart Buck 3 Click driver.
 * @{
 */

/**
 * @defgroup smartbuck3_reg Smart Buck 3 Registers List
 * @brief List of registers of Smart Buck 3 Click driver.
 */

/**
 * @addtogroup smartbuck3_reg
 * @{
 */

/**
 * @brief Smart Buck 3 description register.
 * @details Specified register for description of Smart Buck 3 Click driver.
 */
#define SMARTBUCK3_REG_SET0               0x00
#define SMARTBUCK3_REG_SET1               0x01
#define SMARTBUCK3_REG_CTRL               0x04
#define SMARTBUCK3_REG_TEMP               0x05
#define SMARTBUCK3_REG_RMPCTRL            0x06
#define SMARTBUCK3_REG_CHIP_ID_0          0x08
#define SMARTBUCK3_REG_CHIP_ID_1          0x09

/*! @} */ // smartbuck3_reg

/**
 * @defgroup smartbuck3_set Smart Buck 3 Registers Settings
 * @brief Settings for registers of Smart Buck 3 Click driver.
 */

/**
 * @addtogroup smartbuck3_set
 * @{
 */

/**
 * @brief Smart Buck 3 description setting.
 * @details Specified setting for description of Smart Buck 3 Click driver.
 */
#define SMARTBUCK3_MOD_BIT_MASK           0x80
#define SMARTBUCK3_OP_MODE_FORCED_PWM     0x80
#define SMARTBUCK3_OP_MODE_PFM            0x00
#define SMARTBUCK3_OV_BIT_MASK            0x7F
#define SMARTBUCK3_CTRL_PD_EN             0x80
#define SMARTBUCK3_CTRL_PD_VSEL           0x40
#define SMARTBUCK3_TEMP_DIS_BIT_MASK      0xFB
#define SMARTBUCK3_TEMP_TS_ENABLE         0x00
#define SMARTBUCK3_TEMP_TS_DISABLE        0x04
#define SMARTBUCK3_TEMP_TJEW              0x02
#define SMARTBUCK3_TEMP_TJEW_BIT_MASK     0xFD
#define SMARTBUCK3_TEMP_LT_120_C          0x00
#define SMARTBUCK3_TEMP_GT_120_C          0x01
#define SMARTBUCK3_TEMP_ERROR             0x02
#define SMARTBUCK3_TEMP_TJTS              0x01
#define SMARTBUCK3_RMP_SET                0xE0
#define SMARTBUCK3_RMP_EN_DISC            0x04
#define SMARTBUCK3_RMP_PFM                0x02
#define SMARTBUCK3_ID_VENDOR              0xF0
#define SMARTBUCK3_ID_PART                0x0C
#define SMARTBUCK3_ID_REV                 0x03
#define SMARTBUCK3_VTG_RAMP_T_32mVns      0x00
#define SMARTBUCK3_VTG_RAMP_T_16mVns      0x01
#define SMARTBUCK3_VTG_RAMP_T_8mVns       0x02
#define SMARTBUCK3_VTG_RAMP_T_4mVns       0x03
#define SMARTBUCK3_VTG_RAMP_T_2mVns       0x04
#define SMARTBUCK3_VTG_RAMP_T_1mVns       0x05
#define SMARTBUCK3_VTG_RAMP_T_0_5mVns     0x06
#define SMARTBUCK3_VTG_RAMP_T_0_25mVns    0x07
#define SMARTBUCK3_VTG_RAMP_T_BIT_MASK    0xE0
#define SMARTBUCK3_VOUT_MAX               1770
#define SMARTBUCK3_VOUT_MIN                500
#define SMARTBUCK3_DEVICE_ID              0x91

/**
 * @brief Smart Buck 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Buck 3 Click driver.
 */
#define SMARTBUCK3_DEVICE_ADDRESS         0x60

/*! @} */ // smartbuck3_set

/**
 * @defgroup smartbuck3_map Smart Buck 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Buck 3 Click driver.
 */

/**
 * @addtogroup smartbuck3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Buck 3 Click to the selected MikroBUS.
 */
#define SMARTBUCK3_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // smartbuck3_map
/*! @} */ // smartbuck3

/**
 * @brief Smart Buck 3 Click context object.
 * @details Context object definition of Smart Buck 3 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} smartbuck3_t;

/**
 * @brief Smart Buck 3 Click configuration object.
 * @details Configuration object definition of Smart Buck 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} smartbuck3_cfg_t;

/**
 * @brief Smart Buck 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTBUCK3_OK = 0,
    SMARTBUCK3_ERROR = -1

} smartbuck3_return_value_t;

/*!
 * @addtogroup smartbuck3 Smart Buck 3 Click Driver
 * @brief API for configuring and manipulating Smart Buck 3 Click driver.
 * @{
 */

/**
 * @brief Smart Buck 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartbuck3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartbuck3_cfg_setup ( smartbuck3_cfg_t *cfg );

/**
 * @brief Smart Buck 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartbuck3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_init ( smartbuck3_t *ctx, smartbuck3_cfg_t *cfg );

/**
 * @brief Smart Buck 3 default configuration function.
 * @details This function executes a default configuration of Smart Buck 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartbuck3_default_cfg ( smartbuck3_t *ctx );

/**
 * @brief Smart Buck 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_generic_write ( smartbuck3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart Buck 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_generic_read ( smartbuck3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart Buck 3 set voltage function.
 * @details This function sets the output voltage by using I2C serial interface
 * of the TPS62366A, 4A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[in] vout_mv : Voltage output in millivolts (500mV -1770mV).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_set_voltage ( smartbuck3_t *ctx, uint16_t vout_mv );

/**
 * @brief Smart Buck 3 get voltage function.
 * @details This function read the output voltage by using I2C serial interface
 * of the TPS62366A, 4A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[out] vout_mv : Voltage output in millivolts (500mV -1770mV).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_get_voltage ( smartbuck3_t *ctx, uint16_t *vout_mv );

/**
 * @brief Smart Buck 3 set operation mode function.
 * @details This function set operation mode by using I2C serial interface
 * of the TPS62366A, 4A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[in] op_mode : 
 *         @li @c SMARTBUCK3_OP_MODE_PFM - PFM / PWM mode operation,
 *         @li @c SMARTBUCK3_OP_MODE_FORCED_PWM - Forced PWM mode operation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_set_operation_mode ( smartbuck3_t *ctx, uint8_t op_mode );

/**
 * @brief Smart Buck 3 get operation mode function.
 * @details This function read operation mode by using I2C serial interface
 * of the TPS62366A, 4A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[out] op_mode : 
 *         @li @c SMARTBUCK3_OP_MODE_PFM        - PFM / PWM mode operation,
 *         @li @c SMARTBUCK3_OP_MODE_FORCED_PWM - Forced PWM mode operation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_get_operation_mode ( smartbuck3_t *ctx, uint8_t *op_mode );

/**
 * @brief Smart Buck 3 set temperature shutdown function.
 * @details This function set emperature shutdown feature by using I2C serial interface
 * of the TPS62366A, 4A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[in] temp_enable : 
 *         @li @c SMARTBUCK3_TEMP_TS_ENABLE  - Temperature shutdown enabled,
 *         @li @c SMARTBUCK3_TEMP_TS_DISABLE - Temperature shutdown disabled (not recommended).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_set_temperature_shutdown ( smartbuck3_t *ctx, uint8_t temp_enable );

/**
 * @brief Smart Buck 3 check temperature warning function.
 * @details This function checks temperature warnings by using I2C serial interface
 * of the TPS62366A, 4A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @return @li @c SMARTBUCK3_TEMP_LT_120_C - The temperature is less than 120 degrees Celsius,
 *         @li @c SMARTBUCK3_TEMP_GT_120_C - The temperature is greater than 120 degrees Celsius.
 * @note None.
 */
uint8_t smartbuck3_check_temperature_warning ( smartbuck3_t *ctx );

/**
 * @brief Smart Buck 3 set voltage ramp timing function.
 * @details This function set output voltage ramp timing by using I2C serial interface
 * of the TPS62366A, 4A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[in] slope : 
 *         @li @c SMARTBUCK3_VTG_RAMP_T_32mVns   - 32 mV/µs,
 *         @li @c SMARTBUCK3_VTG_RAMP_T_16mVns   - 16 mV/µs,
 *         @li @c SMARTBUCK3_VTG_RAMP_T_8mVns    -  8 mV/µs,
 *         @li @c SMARTBUCK3_VTG_RAMP_T_4mVns    -  4 mV/µs,
 *         @li @c SMARTBUCK3_VTG_RAMP_T_2mVns    -  2 mV/µs,
 *         @li @c SMARTBUCK3_VTG_RAMP_T_1mVns    -  1 mV/µs,
 *         @li @c SMARTBUCK3_VTG_RAMP_T_0_5mVns  -  0.5 mV/µs,
 *         @li @c SMARTBUCK3_VTG_RAMP_T_0_25mVns -  0.25 mV/µs.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_set_voltage_ramp_timing ( smartbuck3_t *ctx, uint8_t slope );

/**
 * @brief Smart Buck 3 get device ID function.
 * @details This function read device ID by using I2C serial interface
 * of the TPS62366A, 4A Processor Supply with I2C Compatible Interface and Remote Sense
 * on the Smart Buck 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #smartbuck3_t object definition for detailed explanation.
 * @param[out] device_id : Chip ID ( [D7:D4] - Vendor ID 
 *                                   [D3:D2] - Part number ID 
 *                                   [D1:D0] - Chip revision ID ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck3_get_device_id ( smartbuck3_t *ctx, uint8_t *device_id );

#ifdef __cplusplus
}
#endif
#endif // SMARTBUCK3_H

/*! @} */ // smartbuck3

// ------------------------------------------------------------------------ END
