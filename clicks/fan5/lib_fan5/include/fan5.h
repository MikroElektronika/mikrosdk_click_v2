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
 * @file fan5.h
 * @brief This file contains API for Fan 5 Click Driver.
 */

#ifndef FAN5_H
#define FAN5_H

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
 * @addtogroup fan5 Fan 5 Click Driver
 * @brief API for configuring and manipulating Fan 5 Click driver.
 * @{
 */

/**
 * @defgroup fan5_reg Fan 5 Registers List
 * @brief List of registers of Fan 5 Click driver.
 */

/**
 * @addtogroup fan5_reg
 * @{
 */

/**
 * @brief Fan 5 description register.
 * @details Specified register for description of Fan 5 Click driver.
 */
#define FAN5_RPM1_REG                   0x00
#define FAN5_RPM2_REG                   0x01
#define FAN5_FAN_FAULT1_REG             0x02
#define FAN5_FAN_FAULT2_REG             0x03
#define FAN5_CONFIG_REG                 0x04
#define FAN5_STATUS_REG                 0x05
#define FAN5_DUTY_CYCLE_REG             0x06
#define FAN5_MFR_ID_REG                 0x07
#define FAN5_VER_ID_REG                 0x08

/*! @} */ // fan5_reg

/**
 * @defgroup fan5_set Fan 5 Registers Settings
 * @brief Settings for registers of Fan 5 Click driver.
 */

/**
 * @addtogroup fan5_set
 * @{
 */

/**
 * @brief Fan 5 description setting.
 * @details Specified setting for description of Fan 5 Click driver.
 */
#define FAN5_CLEAR_FLT                  0x80
#define FAN5_8_BIT_RESOLUTION           0x00
#define FAN5_9_BIT_RESOLUTION           0x40
#define FAN5_VOUT_BASED_ON_DYTY_REG     0x20
#define FAN5_VOUT_BASED_ON_VIN          0x00
#define FAN5_FAN2_PPR_1                 0x00
#define FAN5_FAN2_PPR_2                 0x08
#define FAN5_FAN2_PPR_4                 0x10
#define FAN5_FAN2_PPR_8                 0x18
#define FAN5_FAN1_PPR_1                 0x00
#define FAN5_FAN1_PPR_2                 0x02
#define FAN5_FAN1_PPR_4                 0x04
#define FAN5_FAN1_PPR_8                 0x06
#define FAN5_SHUTDOWN_MODE              0x01
#define FAN5_NORMAL_MODE                0x00

#define FAN5_MAX_RPM_VALUE              12750

/**
 * @brief Fan 5 fault flags.
 * @details Specified fault flags of Fan 5 Click driver.
 */
#define FAN5_OTF_FLAG                   0x20
#define FAN5_R2CO_FLAG                  0x10
#define FAN5_R1CO_FLAG                  0x08
#define FAN5_VSTAT_FLAG                 0x04
#define FAN5_F2F_FLAG                   0x02
#define FAN5_F1F_FLAG                   0x01

/**
 * @brief Fan 5 duty cycle setting.
 * @details Specified setting for duty cycle of Fan 5 Click driver.
 */
#define FAN5_30_PER_DUTY                0x00
#define FAN5_35_PER_DUTY                0x01
#define FAN5_40_PER_DUTY                0x02
#define FAN5_44_PER_DUTY                0x03
#define FAN5_49_PER_DUTY                0x04
#define FAN5_53_PER_DUTY                0x05
#define FAN5_58_PER_DUTY                0x06
#define FAN5_63_PER_DUTY                0x07
#define FAN5_67_PER_DUTY                0x08
#define FAN5_72_PER_DUTY                0x09
#define FAN5_77_PER_DUTY                0x0A
#define FAN5_81_PER_DUTY                0x0B
#define FAN5_86_PER_DUTY                0x0C
#define FAN5_90_PER_DUTY                0x0D
#define FAN5_95_PER_DUTY                0x0E
#define FAN5_100_PER_DUTY               0x0F

/**
 * @brief Fan 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Fan 5 Click driver.
 */
#define FAN5_DEVICE_ADDRESS             0x1B

/*! @} */ // fan5_set

/**
 * @defgroup fan5_map Fan 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Fan 5 Click driver.
 */

/**
 * @addtogroup fan5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Fan 5 Click to the selected MikroBUS.
 */
#define FAN5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // fan5_map
/*! @} */ // fan5

/**
 * @brief Fan 5 Click context object.
 * @details Context object definition of Fan 5 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t flt;           /**< Fault sence pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} fan5_t;

/**
 * @brief Fan 5 Click configuration object.
 * @details Configuration object definition of Fan 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t flt;             /**< Fault sence pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} fan5_cfg_t;

/**
 * @brief Fan 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FAN5_OK = 0,
    FAN5_ERROR = -1,
    FAN5_FAULT = -2

} fan5_return_value_t;

/*!
 * @addtogroup fan5 Fan 5 Click Driver
 * @brief API for configuring and manipulating Fan 5 Click driver.
 * @{
 */

/**
 * @brief Fan 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #fan5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void fan5_cfg_setup ( fan5_cfg_t *cfg );

/**
 * @brief Fan 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #fan5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_init ( fan5_t *ctx, fan5_cfg_t *cfg );

/**
 * @brief Fan 5 default configuration function.
 * @details This function executes a default configuration of Fan 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t fan5_default_cfg ( fan5_t *ctx );

/**
 * @brief Fan 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_generic_write ( fan5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Fan 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_generic_read ( fan5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Fan 5 I2C writing into register function.
 * @details This function writes a data byte into 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_reg_write ( fan5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Fan 5 I2C reading register function.
 * @details This function reads a byte of data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_reg_read ( fan5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Fan 5 read manufacturer identification.
 * @details This function reads a manufacturer 
 * identification regisret by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[out] mfr_id : Read manufacturer identification.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_get_mfr_id( fan5_t *ctx, uint8_t *mfr_id );

/**
 * @brief Fan 5 get speed of FAN1.
 * @details This function reads the speed of the FAN1 by reading 
 * the appropriate register and multiplying that data with a constant.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[out] fan1_speed : Speed of FAN1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If this value is exceeded, R1CO in the Status Register will be set.
 */
err_t fan5_get_rpm1 ( fan5_t *ctx, uint16_t *fan1_speed );

/**
 * @brief Fan 5 get speed of FAN2.
 * @details This function reads the speed of the FAN2 by reading 
 * the appropriate register and multiplying that data with a constant.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[out] fan2_speed : Speed of FAN2.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If this value is exceeded, R2CO in the Status Register will be set.
 */
err_t fan5_get_rpm2 ( fan5_t *ctx, uint16_t *fan2_speed );

/**
 * @brief Fan 5 set FAN1 fault threshold.
 * @details This function is used to set FAN1 speed threshold, if the speed 
 * drops below this value for more than 2.4 seconds, F1F in the Status Register will be set.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[in] fault1_value : Low speed threshold of FAN1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note RPM threshold can be set in 50 RPM increments.
 */
err_t fan5_set_fan_fault1 ( fan5_t *ctx, uint16_t fault1_value );

/**
 * @brief Fan 5 set FAN2 fault threshold.
 * @details This function is used to set FAN2 speed threshold, if the speed 
 * drops below this value for more than 2.4 seconds, F1F in the Status Register will be set.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[in] fault2_value : Low speed threshold of FAN2.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note RPM threshold can be set in 50 RPM increments.
 */
err_t fan5_set_fan_fault2 ( fan5_t *ctx, uint16_t fault2_value );

/**
 * @brief Fan 5 set duty cycle.
 * @details This function is used to set duty cycle that is used to control speed of the fans.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use predefined values for the duty cycle.
 */
err_t fan5_set_duty_cycle ( fan5_t *ctx, uint8_t duty_cycle );

/**
 * @brief Fan 5 get status flags.
 * @details This function is used to read the status register in order to get 
 * faults that might occur.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @param[out] status_data : Read data from the status register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_get_status_flags (  fan5_t *ctx, uint8_t *status_data );

/**
 * @brief Fan 5 get fault state.
 * @details This function is used to read state of the flt pin.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Fault triggered.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_get_fault_state ( fan5_t *ctx );

/**
 * @brief Fan 5 clear status flags.
 * @details This function is used to clear the status register flags.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_clear_flt_flag ( fan5_t *ctx );

/**
 * @brief Fan 5 turn on fans.
 * @details This function is used to turn on FAN1 and FAN2 outputs.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_turn_on_fans ( fan5_t *ctx );

/**
 * @brief Fan 5 turn off fans.
 * @details This function is used to turn off FAN1 and FAN2 outputs.
 * @param[in] ctx : Click context object.
 * See #fan5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan5_turn_off_fans ( fan5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // FAN5_H

/*! @} */ // fan5

// ------------------------------------------------------------------------ END
