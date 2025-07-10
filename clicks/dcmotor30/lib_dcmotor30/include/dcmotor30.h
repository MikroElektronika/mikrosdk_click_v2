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
 * @file dcmotor30.h
 * @brief This file contains API for DC Motor 30 Click Driver.
 */

#ifndef DCMOTOR30_H
#define DCMOTOR30_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup dcmotor30 DC Motor 30 Click Driver
 * @brief API for configuring and manipulating DC Motor 30 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor30_reg DC Motor 30 Registers List
 * @brief List of registers of DC Motor 30 Click driver.
 */

/**
 * @addtogroup dcmotor30_reg
 * @{
 */

/**
 * @brief DC Motor 30 register map.
 * @details Specified register map of DC Motor 30 Click driver.
 */
#define DCMOTOR30_REG_FAULT_STATUS          0x00
#define DCMOTOR30_REG_RC_STATUS1            0x01
#define DCMOTOR30_REG_RC_STATUS2            0x02
#define DCMOTOR30_REG_RC_STATUS3            0x03
#define DCMOTOR30_REG_STATUS1               0x04
#define DCMOTOR30_REG_STATUS2               0x05
#define DCMOTOR30_REG_STATUS3               0x06
#define DCMOTOR30_REG_STATUS4               0x07
#define DCMOTOR30_REG_STATUS5               0x08
#define DCMOTOR30_REG_CONFIG0               0x09
#define DCMOTOR30_REG_CONFIG1               0x0A
#define DCMOTOR30_REG_CONFIG2               0x0B
#define DCMOTOR30_REG_CONFIG3               0x0C
#define DCMOTOR30_REG_CONFIG4               0x0D
#define DCMOTOR30_REG_CTRL0                 0x0E
#define DCMOTOR30_REG_CTRL1                 0x0F
#define DCMOTOR30_REG_CTRL2                 0x10
#define DCMOTOR30_REG_RC_CTRL0              0x11
#define DCMOTOR30_REG_RC_CTRL1              0x12
#define DCMOTOR30_REG_RC_CTRL2              0x13
#define DCMOTOR30_REG_RC_CTRL3              0x14
#define DCMOTOR30_REG_RC_CTRL4              0x15
#define DCMOTOR30_REG_RC_CTRL5              0x16
#define DCMOTOR30_REG_RC_CTRL6              0x17
#define DCMOTOR30_REG_RC_CTRL7              0x18
#define DCMOTOR30_REG_RC_CTRL8              0x19

/*! @} */ // dcmotor30_reg

/**
 * @defgroup dcmotor30_set DC Motor 30 Registers Settings
 * @brief Settings for registers of DC Motor 30 Click driver.
 */

/**
 * @addtogroup dcmotor30_set
 * @{
 */

/**
 * @brief DC Motor 30 FAULT_STATUS register setting.
 * @details Specified setting for FAULT_STATUS register of DC Motor 30 Click driver.
 */
#define DCMOTOR30_FAULT_STATUS_FAULT        0x80
#define DCMOTOR30_FAULT_STATUS_STALL        0x20
#define DCMOTOR30_FAULT_STATUS_OCP          0x10
#define DCMOTOR30_FAULT_STATUS_OVP          0x08
#define DCMOTOR30_FAULT_STATUS_TSD          0x04
#define DCMOTOR30_FAULT_STATUS_NPOR         0x02

/**
 * @brief DC Motor 30 CONFIG0 register setting.
 * @details Specified setting for CONFIG0 register of DC Motor 30 Click driver.
 */
#define DCMOTOR30_CONFIG0_EN_OUT            0x80
#define DCMOTOR30_CONFIG0_EN_OVP            0x40
#define DCMOTOR30_CONFIG0_EN_STALL          0x20
#define DCMOTOR30_CONFIG0_VSNS_SEL_AN       0x00
#define DCMOTOR30_CONFIG0_VSNS_SEL_DIG      0x10
#define DCMOTOR30_CONFIG0_VSNS_SEL_MASK     0x10
#define DCMOTOR30_CONFIG0_CLR_FLT           0x02
#define DCMOTOR30_CONFIG0_DUTY_CTRL_EN      0x01

/**
 * @brief DC Motor 30 current calculation setting.
 * @details Specified setting for current calculation of DC Motor 30 Click driver.
 */
#define DCMOTOR30_RIPROPI_V_TO_MA           1.5
#define DCMOTOR30_SCALING_FACTOR            1.5

/**
 * @brief DC Motor 30 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of DC Motor 30 Click driver.
 */
#define DCMOTOR30_NUM_CONVERSIONS           200

/**
 * @brief DC Motor 30 ADC setting.
 * @details Specified settings for ADC of DC Motor 30 Click driver.
 */
#define DCMOTOR30_VREF_3V3                  3.3
#define DCMOTOR30_VREF_5V                   5.0
#define DCMOTOR30_VREF_DEFAULT              DCMOTOR30_VREF_3V3

/**
 * @brief DC Motor 30 timeout setting.
 * @details Specified setting for timeout of DC Motor 30 Click driver.
 */
#define DCMOTOR30_TIMEOUT_MS                2000

/**
 * @brief DC Motor 30 motor PWM control mode setting.
 * @details Specified setting for motor PWM control mode of DC Motor 30 Click driver.
 */
#define DCMOTOR30_MOTOR_COAST               0
#define DCMOTOR30_MOTOR_FORWARD             1
#define DCMOTOR30_MOTOR_REVERSE             2
#define DCMOTOR30_MOTOR_BRAKE               3

/**
 * @brief DC Motor 30 device address setting.
 * @details Specified setting for device slave address selection of
 * DC Motor 30 Click driver.
 */
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_00    0x30
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_0Z    0x31
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_01    0x32
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_Z0    0x33
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_ZZ    0x34
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_Z1    0x35
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_10    0x36
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_1Z    0x37
#define DCMOTOR30_DEVICE_ADDRESS_A1A0_11    0x38

/*! @} */ // dcmotor30_set

/**
 * @defgroup dcmotor30_map DC Motor 30 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 30 Click driver.
 */

/**
 * @addtogroup dcmotor30_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 30 Click to the selected MikroBUS.
 */
#define DCMOTOR30_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ipropi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor30_map
/*! @} */ // dcmotor30

/**
 * @brief DC Motor 30 Click context object.
 * @details Context object definition of DC Motor 30 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t in2;          /**< H-Bridge control pin 2. */
    digital_out_t in1;          /**< H-Bridge control pin 1. */

    // Input pins
    digital_in_t fault;         /**< Fault indicator pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    analog_in_t adc;            /**< ADC module object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float zero_curr_offset;     /**< Voltage offset for zero current (COAST mode). */

} dcmotor30_t;

/**
 * @brief DC Motor 30 Click configuration object.
 * @details Configuration object definition of DC Motor 30 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t ipropi;          /**< Current monitoring ADC pin. */

    pin_name_t in2;             /**< H-Bridge control pin 2. */
    pin_name_t in1;             /**< H-Bridge control pin 1. */
    pin_name_t fault;           /**< Fault indicator pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} dcmotor30_cfg_t;

/**
 * @brief DC Motor 30 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR30_OK = 0,
    DCMOTOR30_ERROR = -1

} dcmotor30_return_value_t;

/*!
 * @addtogroup dcmotor30 DC Motor 30 Click Driver
 * @brief API for configuring and manipulating DC Motor 30 Click driver.
 * @{
 */

/**
 * @brief DC Motor 30 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor30_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor30_cfg_setup ( dcmotor30_cfg_t *cfg );

/**
 * @brief DC Motor 30 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor30_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor30_init ( dcmotor30_t *ctx, dcmotor30_cfg_t *cfg );

/**
 * @brief DC Motor 30 default configuration function.
 * @details This function executes a default configuration of DC Motor 30
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor30_default_cfg ( dcmotor30_t *ctx );

/**
 * @brief DC Motor 30 write reg function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor30_write_reg ( dcmotor30_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DC Motor 30 read reg function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor30_read_reg ( dcmotor30_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DC Motor 30 read raw IPROPI ADC value function.
 * @details This function reads results of AD conversion of the IPROPI pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor30_read_adc_raw ( dcmotor30_t *ctx, uint16_t *data_out );

/**
 * @brief DC Motor 30 read IPROPI pin voltage level function.
 * @details This function reads results of AD conversion of the IPROPI pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor30_read_adc_volt ( dcmotor30_t *ctx, float *data_out );

/**
 * @brief DC Motor 30 read IPROPI pin voltage level average function.
 * @details This function a desired number of IPROPI pin ADC voltage samples and averages it.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] volt_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor30_read_adc_volt_avg ( dcmotor30_t *ctx, uint16_t num_conv, float *volt_avg );

/**
 * @brief DC Motor 30 set vref function.
 * @details This function sets the ADC voltage reference for DC Motor 30 Click driver.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b dcmotor30_init is 3.3V.
 */
err_t dcmotor30_set_adc_vref ( dcmotor30_t *ctx, float vref );

/**
 * @brief DC Motor 30 set IN1 pin function.
 * @details This function sets the IN1 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor30_set_in1_pin ( dcmotor30_t *ctx );

/**
 * @brief DC Motor 30 clear IN1 pin function.
 * @details This function clears the IN1 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor30_clear_in1_pin ( dcmotor30_t *ctx );

/**
 * @brief DC Motor 30 set IN2 pin function.
 * @details This function sets the IN2 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor30_set_in2_pin ( dcmotor30_t *ctx );

/**
 * @brief DC Motor 30 clear IN2 pin function.
 * @details This function clears the IN2 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor30_clear_in2_pin ( dcmotor30_t *ctx );

/**
 * @brief DC Motor 30 get FAULT pin function.
 * @details This function returns the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dcmotor30_get_fault_pin ( dcmotor30_t *ctx );

/**
 * @brief DC Motor 30 drive motor function.
 * @details This function drives the motor in the selected PWM control mode state.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Coast,
 *                    @li @c 1 - Forward,
 *                    @li @c 2 - Reverse,
 *                    @li @c 3 - Brake.
 * @return None.
 * @note None.
 */
void dcmotor30_drive_motor ( dcmotor30_t *ctx, uint8_t state );

/**
 * @brief DC Motor 30 clear fault function.
 * @details This function clears all latched faults.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor30_clear_fault ( dcmotor30_t *ctx );

/**
 * @brief DC Motor 30 calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor30_calib_offset ( dcmotor30_t *ctx );

/**
 * @brief DC Motor 30 get out current function.
 * @details This function reads the current output measurement in mA.
 * @param[in] ctx : Click context object.
 * See #dcmotor30_t object definition for detailed explanation.
 * @param[out] current : Current output level [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero current offset, see dcmotor30_calib_offset function.
 */
err_t dcmotor30_get_out_current ( dcmotor30_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR30_H

/*! @} */ // dcmotor30

// ------------------------------------------------------------------------ END
