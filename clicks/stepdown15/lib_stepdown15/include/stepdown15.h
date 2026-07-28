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
 * @file stepdown15.h
 * @brief This file contains API for Step Down 15 Click Driver.
 */

#ifndef STEPDOWN15_H
#define STEPDOWN15_H

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
 * @addtogroup stepdown15 Step Down 15 Click Driver
 * @brief API for configuring and manipulating Step Down 15 Click driver.
 * @{
 */

/**
 * @defgroup stepdown15_reg Step Down 15 Registers List
 * @brief List of registers of Step Down 15 Click driver.
 */

/**
 * @addtogroup stepdown15_reg
 * @{
 */

/**
 * @brief Step Down 15 direct I2C register map.
 * @details Specified direct I2C register map of Step Down 15 Click driver.
 */
#define STEPDOWN15_REG_I2C_BASE                     0x20
#define STEPDOWN15_REG_PMBUS_BASE                   0x21
#define STEPDOWN15_REG_OPERATION                    0x22
#define STEPDOWN15_REG_ON_OFF_CONFIG                0x23
#define STEPDOWN15_REG_WRITE_PROTECT                0x24
#define STEPDOWN15_REG_VOUT_MODE                    0x2B
#define STEPDOWN15_REG_VOUT_COMMAND_LOWER           0x2C
#define STEPDOWN15_REG_VOUT_COMMAND_UPPER           0x2D
#define STEPDOWN15_REG_VOUT_MAX_LOWER               0x2E
#define STEPDOWN15_REG_VOUT_MAX_UPPER               0x2F
#define STEPDOWN15_REG_BUS_VOLTAGE                  0x7A
#define STEPDOWN15_REG_CLEAR_STATUS                 0x8C
#define STEPDOWN15_REG_STATUS                       0x93
#define STEPDOWN15_REG_IC_REV_BYTE_COUNT            0x94
#define STEPDOWN15_REG_IC_REV                       0x95
#define STEPDOWN15_REG_IC_DEV_ID_COUNT              0x96
#define STEPDOWN15_REG_IC_DEV_ID                    0x97
#define STEPDOWN15_REG_PVIN_REPORT_LOWER            0x9A
#define STEPDOWN15_REG_PVIN_REPORT_UPPER            0x9B
#define STEPDOWN15_REG_VOUT_REPORT_LOWER            0xA0
#define STEPDOWN15_REG_VOUT_REPORT_UPPER            0xA1
#define STEPDOWN15_REG_TEMP_REPORT_LOWER            0xA2
#define STEPDOWN15_REG_TEMP_REPORT_UPPER            0xA3
#define STEPDOWN15_REG_VCC_REPORT_LOWER             0xA4
#define STEPDOWN15_REG_VCC_REPORT_UPPER             0xA5

/*! @} */ // stepdown15_reg

/**
 * @defgroup stepdown15_set Step Down 15 Registers Settings
 * @brief Settings for registers of Step Down 15 Click driver.
 */

/**
 * @addtogroup stepdown15_set
 * @{
 */

/**
 * @brief Step Down 15 OPERATION register setting.
 * @details Specified setting for OPERATION register of Step Down 15 Click driver.
 */
#define STEPDOWN15_OPERATION_OUTPUT_OFF             0x00
#define STEPDOWN15_OPERATION_OUTPUT_ON              0x80
#define STEPDOWN15_OPERATION_OUTPUT_MASK            0x80
#define STEPDOWN15_OPERATION_PDOWN_IMMEDIATELY      0x00
#define STEPDOWN15_OPERATION_PDOWN_DELAY            0x40
#define STEPDOWN15_OPERATION_PDOWN_MASK             0x40
#define STEPDOWN15_OPERATION_VCMD_COMMAND           0x00
#define STEPDOWN15_OPERATION_VCMD_MARGIN_LOW        0x10
#define STEPDOWN15_OPERATION_VCMD_MARGIN_HIGH       0x20
#define STEPDOWN15_OPERATION_VCMD_AVS_BUS           0x30
#define STEPDOWN15_OPERATION_VCMD_MASK              0x30

/**
 * @brief Step Down 15 STATUS register setting.
 * @details Specified setting for STATUS register of Step Down 15 Click driver.
 */
#define STEPDOWN15_STATUS_POWER_GOOD                0x80
#define STEPDOWN15_STATUS_OVERVOLTAGE               0x40
#define STEPDOWN15_STATUS_OVERCURRENT               0x20
#define STEPDOWN15_STATUS_TEMPERATURE               0x10
#define STEPDOWN15_STATUS_ENABLE                    0x08
#define STEPDOWN15_STATUS_USER_NVM_WRITE            0x02
#define STEPDOWN15_STATUS_CLEARED                   0x01

/**
 * @brief Step Down 15 output calculation setting.
 * @details Specified setting for output calculation of Step Down 15 Click driver.
 */
#define STEPDOWN15_VOUT_MIN                         0.6
#define STEPDOWN15_VOUT_MAX                         1.8
#define STEPDOWN15_VOUT_RES                         256.0f
#define STEPDOWN15_ROUND_TO_NEAREAST_INT            0.5f
#define STEPDOWN15_TEMP_NUM_MEASUREMENTS            100

/**
 * @brief Step Down 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Down 15 Click driver.
 */
#define STEPDOWN15_DEVICE_ADDRESS_ADDR_GND          0x08
#define STEPDOWN15_DEVICE_ADDRESS_ADDR_1K13         0x09
#define STEPDOWN15_DEVICE_ADDRESS_ADDR_1K87         0x0A
#define STEPDOWN15_DEVICE_ADDRESS_ADDR_2K61         0x0B
#define STEPDOWN15_DEVICE_ADDRESS_ADDR_4K12         0x0D
#define STEPDOWN15_DEVICE_ADDRESS_ADDR_4K87         0x0E

/*! @} */ // stepdown15_set

/**
 * @defgroup stepdown15_map Step Down 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 15 Click driver.
 */

/**
 * @addtogroup stepdown15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 15 Click to the selected MikroBUS.
 */
#define STEPDOWN15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepdown15_map
/*! @} */ // stepdown15

/**
 * @brief Step Down 15 Click context object.
 * @details Context object definition of Step Down 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Description. */
    digital_out_t pwm;          /**< Description. */

    // Input pins
    digital_in_t alert;         /**< Description. */
    digital_in_t pg;            /**< Description. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepdown15_t;

/**
 * @brief Step Down 15 Click configuration object.
 * @details Configuration object definition of Step Down 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alert;           /**< Description. */
    pin_name_t en;              /**< Description. */
    pin_name_t pwm;             /**< Description. */
    pin_name_t pg;              /**< Description. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepdown15_cfg_t;

/**
 * @brief Step Down 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN15_OK = 0,
    STEPDOWN15_ERROR = -1

} stepdown15_return_value_t;

/*!
 * @addtogroup stepdown15 Step Down 15 Click Driver
 * @brief API for configuring and manipulating Step Down 15 Click driver.
 * @{
 */

/**
 * @brief Step Down 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown15_cfg_setup ( stepdown15_cfg_t *cfg );

/**
 * @brief Step Down 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_init ( stepdown15_t *ctx, stepdown15_cfg_t *cfg );

/**
 * @brief Step Down 15 default configuration function.
 * @details This function executes a default configuration of Step Down 15
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepdown15_default_cfg ( stepdown15_t *ctx );

/**
 * @brief Step Down 15 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_write_reg ( stepdown15_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Step Down 15 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_write_regs ( stepdown15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Step Down 15 write 16-bit register function.
 * @details This function writes a 16-bit value to the selected register in little-endian format.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data value to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_write_reg_16 ( stepdown15_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Step Down 15 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_read_reg ( stepdown15_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Step Down 15 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_read_regs ( stepdown15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Step Down 15 read 16-bit register function.
 * @details This function reads a 16-bit value from the selected register in little-endian format.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data value will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_read_reg_16 ( stepdown15_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Step Down 15 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown15_enable_device ( stepdown15_t *ctx );

/**
 * @brief Step Down 15 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown15_disable_device ( stepdown15_t *ctx );

/**
 * @brief Step Down 15 set PWM pin function.
 * @details This function sets the PWM pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void stepdown15_set_pwm_pin ( stepdown15_t *ctx, uint8_t state );

/**
 * @brief Step Down 15 get PG pin function.
 * @details This function returns the PG pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepdown15_get_pg_pin ( stepdown15_t *ctx );

/**
 * @brief Step Down 15 get ALERT pin function.
 * @details This function returns the ALERT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepdown15_get_alert_pin ( stepdown15_t *ctx );

/**
 * @brief Step Down 15 set output voltage function.
 * @details This function sets the output voltage command value.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[in] voltage : Target output voltage value [from 0.6V to 1.8V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The target voltage is limited to the supported output voltage range.
 */
err_t stepdown15_set_vout ( stepdown15_t *ctx, float voltage );

/**
 * @brief Step Down 15 read output voltage function.
 * @details This function reads and calculates the output voltage value.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[out] voltage : Pointer to the memory location where the output voltage will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_read_vout ( stepdown15_t *ctx, float *voltage );

/**
 * @brief Step Down 15 read PVIN function.
 * @details This function reads and calculates the input voltage value.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[out] voltage : Pointer to the memory location where the input voltage will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_read_pvin ( stepdown15_t *ctx, float *voltage );

/**
 * @brief Step Down 15 read temperature function.
 * @details This function reads and calculates the average temperature value.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[out] temp_c : Pointer to the memory location where the temperature value will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_read_temperature ( stepdown15_t *ctx, float *temp_c );

/**
 * @brief Step Down 15 read VCC function.
 * @details This function reads and calculates the VCC voltage value.
 * @param[in] ctx : Click context object.
 * See #stepdown15_t object definition for detailed explanation.
 * @param[out] voltage : Pointer to the memory location where the VCC voltage will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown15_read_vcc ( stepdown15_t *ctx, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN15_H

/*! @} */ // stepdown15

// ------------------------------------------------------------------------ END
