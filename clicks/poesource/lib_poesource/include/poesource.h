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
 * @file poesource.h
 * @brief This file contains API for PoE Source Click Driver.
 */

#ifndef POESOURCE_H
#define POESOURCE_H

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
 * @addtogroup poesource PoE Source Click Driver
 * @brief API for configuring and manipulating PoE Source Click driver.
 * @{
 */

/**
 * @defgroup poesource_reg PoE Source Registers List
 * @brief List of registers of PoE Source Click driver.
 */

/**
 * @addtogroup poesource_reg
 * @{
 */

/**
 * @brief PoE Source register map.
 * @details Specified register map of PoE Source Click driver.
 */
#define POESOURCE_REG_INTERRUPT                         0x00
#define POESOURCE_REG_INTERRUPT_MASK                    0x01
#define POESOURCE_REG_INTERRUPT_PRIORITY                0x02
#define POESOURCE_REG_MODE_SETTING                      0x03
#define POESOURCE_REG_MIDSPAN_SETTING                   0x04
#define POESOURCE_REG_PORT_ENABLE                       0x05
#define POESOURCE_REG_DET_CLS_ENABLE                    0x06
#define POESOURCE_REG_DISCONNECT_ENABLE                 0x07
#define POESOURCE_REG_FAULT_TIMER                       0x08
#define POESOURCE_REG_FOLDBACK_ILIM                     0x0B
#define POESOURCE_REG_TWO_EVENT_CLASS_5_ENABLE          0x0C
#define POESOURCE_REG_INTERRUPT_ENABLE                  0x0E
#define POESOURCE_REG_GENERAL_CONTROL                   0x0F
#define POESOURCE_REG_DET_CLS_TRIGGER                   0x10
#define POESOURCE_REG_POWER_ON_OFF_TRIGGER              0x11
#define POESOURCE_REG_LEGACY_ENABLE                     0x12
#define POESOURCE_REG_ICUT_THRESHOLD                    0x13
#define POESOURCE_REG_ILIM_THRESHOLD                    0x17
#define POESOURCE_REG_POWER_SOURCE_STATUS1              0x20
#define POESOURCE_REG_POWER_SOURCE_STATUS1_CLR          0x21
#define POESOURCE_REG_POWER_SOURCE_STATUS2              0x22
#define POESOURCE_REG_POWER_SOURCE_STATUS2_CLR          0x23
#define POESOURCE_REG_DET_CLS_COMPLETE_STATUS           0x24
#define POESOURCE_REG_DET_CLS_COMPLETE_STATUS_CLR       0x25
#define POESOURCE_REG_DET_CLS_RESULT                    0x26
#define POESOURCE_REG_POWER_STATUS                      0x2A
#define POESOURCE_REG_POWER_STATUS_CHANGE               0x2B
#define POESOURCE_REG_POWER_STATUS_CHANGE_CLR           0x2C
#define POESOURCE_REG_OVER_LOAD_STATUS                  0x2D
#define POESOURCE_REG_OVER_LOAD_STATUS_CLR              0x2E
#define POESOURCE_REG_CURRENT_LIMIT_STATUS              0x2F
#define POESOURCE_REG_CURRENT_LIMIT_STATUS_CLR          0x30
#define POESOURCE_REG_DISCONNECT_STATUS                 0x31
#define POESOURCE_REG_DISCONNECT_STATUS_CLR             0x32
#define POESOURCE_REG_WATCHDOG_STATUS                   0x33
#define POESOURCE_REG_PIN_STATUS                        0x34
#define POESOURCE_REG_LEGACY_DETECT_RESULT              0x35
#define POESOURCE_REG_PORT_CURRENT_LSB                  0x40
#define POESOURCE_REG_PORT_CURRENT_MSB                  0x41
#define POESOURCE_REG_OUT_PIN_VOLTAGE_LSB               0x42
#define POESOURCE_REG_OUT_PIN_VOLTAGE_MSB               0x43
#define POESOURCE_REG_INPUT_VOLTAGE_LSB                 0x50
#define POESOURCE_REG_INPUT_VOLTAGE_MSB                 0x51
#define POESOURCE_REG_JUNCTION_TEMPERATURE_LSB          0x52
#define POESOURCE_REG_JUNCTION_TEMPERATURE_MSB          0x53
#define POESOURCE_REG_DIE_ID                            0x60

/*! @} */ // poesource_reg

/**
 * @defgroup poesource_set PoE Source Registers Settings
 * @brief Settings for registers of PoE Source Click driver.
 */

/**
 * @addtogroup poesource_set
 * @{
 */

/**
 * @brief PoE Source MODE_SETTING register setting.
 * @details Specified setting for MODE_SETTING register of PoE Source Click driver.
 */
#define POESOURCE_MODE_SETTING_MODE_SHUTDOWN            0x00
#define POESOURCE_MODE_SETTING_MODE_MANUAL              0x01
#define POESOURCE_MODE_SETTING_MODE_SEMI_AUTO           0x02
#define POESOURCE_MODE_SETTING_MODE_AUTO                0x03
#define POESOURCE_MODE_SETTING_MODE_MASK                0x03

/**
 * @brief PoE Source MIDSPAN_SETTING register setting.
 * @details Specified setting for MIDSPAN_SETTING register of PoE Source Click driver.
 */
#define POESOURCE_MIDSPAN_SETTING_MID_DISABLE           0x00
#define POESOURCE_MIDSPAN_SETTING_MID_ENABLE            0x01
#define POESOURCE_MIDSPAN_SETTING_MID_MASK              0x01

/**
 * @brief PoE Source PORT_ENABLE register setting.
 * @details Specified setting for PORT_ENABLE register of PoE Source Click driver.
 */
#define POESOURCE_PORT_ENABLE_ENAL_DISABLE              0x00
#define POESOURCE_PORT_ENABLE_ENAL_ENABLE               0x10
#define POESOURCE_PORT_ENABLE_ENAL_MASK                 0x10
#define POESOURCE_PORT_ENABLE_EN_DISABLE                0x00
#define POESOURCE_PORT_ENABLE_EN_ENABLE                 0x01
#define POESOURCE_PORT_ENABLE_EN_MASK                   0x01

/**
 * @brief PoE Source DET/CLS_ENABLE register setting.
 * @details Specified setting for DET/CLS_ENABLE register of PoE Source Click driver.
 */
#define POESOURCE_DET_CLS_ENABLE_CLSEN_DISABLE          0x00
#define POESOURCE_DET_CLS_ENABLE_CLSEN_ENABLE           0x10
#define POESOURCE_DET_CLS_ENABLE_CLSEN_MASK             0x10
#define POESOURCE_DET_CLS_ENABLE_DETEN_DISABLE          0x00
#define POESOURCE_DET_CLS_ENABLE_DETEN_ENABLE           0x01
#define POESOURCE_DET_CLS_ENABLE_DETEN_MASK             0x01

/**
 * @brief PoE Source DISCONNECT_ENABLE register setting.
 * @details Specified setting for DISCONNECT_ENABLE register of PoE Source Click driver.
 */
#define POESOURCE_DISCONNECT_ENABLE_DISEN_DISABLE       0x00
#define POESOURCE_DISCONNECT_ENABLE_DISEN_ENABLE        0x01
#define POESOURCE_DISCONNECT_ENABLE_DISEN_MASK          0x01

/**
 * @brief PoE Source GENERAL_CONTROL register setting.
 * @details Specified setting for GENERAL_CONTROL register of PoE Source Click driver.
 */
#define POESOURCE_GENERAL_CONTROL_ADCEN_DISABLE         0x00
#define POESOURCE_GENERAL_CONTROL_ADCEN_ENABLE          0x02
#define POESOURCE_GENERAL_CONTROL_ADCEN_MASK            0x02
#define POESOURCE_GENERAL_CONTROL_WDEN_DISABLE          0x00
#define POESOURCE_GENERAL_CONTROL_WDEN_ENABLE           0x01
#define POESOURCE_GENERAL_CONTROL_WDEN_MASK             0x01

/**
 * @brief PoE Source DET_CLS_RESULT register setting.
 * @details Specified setting for DET_CLS_RESULT register of PoE Source Click driver.
 */
#define POESOURCE_DET_CLS_RESULT_CLSR_NOT_DONE          0x00
#define POESOURCE_DET_CLS_RESULT_CLSR_CLASS_1           0x10
#define POESOURCE_DET_CLS_RESULT_CLSR_CLASS_2           0x20
#define POESOURCE_DET_CLS_RESULT_CLSR_CLASS_3           0x30
#define POESOURCE_DET_CLS_RESULT_CLSR_CLASS_4           0x40
#define POESOURCE_DET_CLS_RESULT_CLSR_CLASS_5           0x50
#define POESOURCE_DET_CLS_RESULT_CLSR_CLASS_0           0x60
#define POESOURCE_DET_CLS_RESULT_CLSR_OC_CONDITION      0x70
#define POESOURCE_DET_CLS_RESULT_CLSR_NOT_MATCH         0x80
#define POESOURCE_DET_CLS_RESULT_CLSR_MASK              0xF0
#define POESOURCE_DET_CLS_RESULT_2EVNTC_NOT_COMPLETED   0x00
#define POESOURCE_DET_CLS_RESULT_2EVNTC_COMPLETED       0x08
#define POESOURCE_DET_CLS_RESULT_2EVNTC_MASK            0x08
#define POESOURCE_DET_CLS_RESULT_DETR_NOT_COMPLETED     0x00
#define POESOURCE_DET_CLS_RESULT_DETR_SHORTED           0x01
#define POESOURCE_DET_CLS_RESULT_DETR_CAP_HIGH          0x02
#define POESOURCE_DET_CLS_RESULT_DETR_RDET_LOW          0x03
#define POESOURCE_DET_CLS_RESULT_DETR_VALID             0x04
#define POESOURCE_DET_CLS_RESULT_DETR_RDET_HIGH         0x05
#define POESOURCE_DET_CLS_RESULT_DETR_PORT_OPEN         0x06
#define POESOURCE_DET_CLS_RESULT_DETR_LOW_IMPEDANCE     0x07
#define POESOURCE_DET_CLS_RESULT_DETR_MASK              0x07

/**
 * @brief PoE Source ADC settings for temperature, Vin, Vout, and Iout calculation.
 * @details Specified ADC settings for temperature, Vin, Vout, and Iout calculation of PoE Source Click driver.
 */
#define POESOURCE_ADC_NUM_CONVERSIONS                   100
#define POESOURCE_ADC_TIMEOUT_MS                        1000
#define POESOURCE_ADC_IOUT_RES                          2.4
#define POESOURCE_ADC_IOUT_OFFSET                       10.0
#define POESOURCE_ADC_VOUT_RES                          0.15
#define POESOURCE_ADC_VIN_RES                           0.15
#define POESOURCE_ADC_TEMP_RES                          0.4
#define POESOURCE_ADC_TEMP_OFFSET                       40.0

/**
 * @brief PoE Source device address setting.
 * @details Specified setting for device slave address selection of
 * PoE Source Click driver.
 */
#define POESOURCE_DEVICE_ADDRESS_0                      0x20
#define POESOURCE_DEVICE_ADDRESS_1                      0x21
#define POESOURCE_DEVICE_ADDRESS_2                      0x22
#define POESOURCE_DEVICE_ADDRESS_3                      0x23
#define POESOURCE_DEVICE_ADDRESS_4                      0x24
#define POESOURCE_DEVICE_ADDRESS_5                      0x25
#define POESOURCE_DEVICE_ADDRESS_6                      0x26
#define POESOURCE_DEVICE_ADDRESS_7                      0x27
#define POESOURCE_DEVICE_ADDRESS_8                      0x28
#define POESOURCE_DEVICE_ADDRESS_9                      0x29
#define POESOURCE_DEVICE_ADDRESS_10                     0x2A
#define POESOURCE_DEVICE_ADDRESS_11                     0x2B
#define POESOURCE_DEVICE_ADDRESS_12                     0x2C
#define POESOURCE_DEVICE_ADDRESS_13                     0x2D
#define POESOURCE_DEVICE_ADDRESS_14                     0x2E
#define POESOURCE_DEVICE_ADDRESS_15                     0x2F

/*! @} */ // poesource_set

/**
 * @defgroup poesource_map PoE Source MikroBUS Map
 * @brief MikroBUS pin mapping of PoE Source Click driver.
 */

/**
 * @addtogroup poesource_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PoE Source Click to the selected MikroBUS.
 */
#define POESOURCE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // poesource_map
/*! @} */ // poesource

/**
 * @brief PoE Source Click context object.
 * @details Context object definition of PoE Source Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt request pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} poesource_t;

/**
 * @brief PoE Source Click configuration object.
 * @details Configuration object definition of PoE Source Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t int_pin;         /**< Interrupt request pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} poesource_cfg_t;

/**
 * @brief PoE Source Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    POESOURCE_OK = 0,
    POESOURCE_ERROR = -1

} poesource_return_value_t;

/*!
 * @addtogroup poesource PoE Source Click Driver
 * @brief API for configuring and manipulating PoE Source Click driver.
 * @{
 */

/**
 * @brief PoE Source configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #poesource_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void poesource_cfg_setup ( poesource_cfg_t *cfg );

/**
 * @brief PoE Source initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #poesource_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t poesource_init ( poesource_t *ctx, poesource_cfg_t *cfg );

/**
 * @brief PoE Source default configuration function.
 * @details This function executes a default configuration of PoE Source
 * Click board.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t poesource_default_cfg ( poesource_t *ctx );

/**
 * @brief PoE Source write register function.
 * @details This function writes one byte to the selected register using the multiple register write function.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t poesource_write_reg ( poesource_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PoE Source write registers function.
 * @details This function writes multiple bytes to the selected register over I2C.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Pointer to the data buffer to write.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t poesource_write_regs ( poesource_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief PoE Source read register function.
 * @details This function reads one byte from the selected register using the multiple register read function.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t poesource_read_reg ( poesource_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PoE Source read registers function.
 * @details This function reads multiple bytes from the selected register over I2C.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data will be stored.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t poesource_read_regs ( poesource_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief PoE Source enable device function.
 * @details This function enables the device by setting the enable pin to a high logic level.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void poesource_enable_device ( poesource_t *ctx );

/**
 * @brief PoE Source disable device function.
 * @details This function disables the device by setting the enable pin to a low logic level.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void poesource_disable_device ( poesource_t *ctx );

/**
 * @brief PoE Source get interrupt pin function.
 * @details This function reads the interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t poesource_get_int_pin ( poesource_t *ctx );

/**
 * @brief PoE Source read ADC function.
 * @details This function reads the selected ADC register value and stores the converted result.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[in] reg : ADC register address.
 * @param[out] adc_data : Pointer to the memory location where the ADC data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns error if the selected register is not a valid ADC register.
 */
err_t poesource_read_adc ( poesource_t *ctx, uint8_t reg, uint16_t *adc_data );

/**
 * @brief PoE Source read average ADC function.
 * @details This function reads and calculates the average ADC value for the selected register.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[in] reg : ADC register address.
 * @param[in] num_conv : Number of conversions used for averaging.
 * @param[out] adc_data_avg : Pointer to the memory location where the average ADC value will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns error if the conversion timeout expires.
 */
err_t poesource_read_adc_avg ( poesource_t *ctx, uint8_t reg, uint16_t num_conv, uint16_t *adc_data_avg );

/**
 * @brief PoE Source read output current function.
 * @details This function reads and calculates the output current value in mA.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[out] current : Pointer to the memory location where the output current will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t poesource_read_iout ( poesource_t *ctx, float *current );

/**
 * @brief PoE Source read output voltage function.
 * @details This function reads and calculates the output voltage value.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[out] voltage : Pointer to the memory location where the output voltage will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The output voltage is calculated from the input and output ADC values.
 */
err_t poesource_read_vout ( poesource_t *ctx, float *voltage );

/**
 * @brief PoE Source read input voltage function.
 * @details This function reads and calculates the input voltage value.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[out] voltage : Pointer to the memory location where the input voltage will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t poesource_read_vin ( poesource_t *ctx, float *voltage );

/**
 * @brief PoE Source read die temperature function.
 * @details This function reads and calculates the die temperature value.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to the memory location where the temperature value will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t poesource_read_die_temp ( poesource_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // POESOURCE_H

/*! @} */ // poesource

// ------------------------------------------------------------------------ END
