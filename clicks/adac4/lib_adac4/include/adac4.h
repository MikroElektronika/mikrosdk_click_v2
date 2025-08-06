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
 * @file adac4.h
 * @brief This file contains API for ADAC 4 Click Driver.
 */

#ifndef ADAC4_H
#define ADAC4_H

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
 * @addtogroup adac4 ADAC 4 Click Driver
 * @brief API for configuring and manipulating ADAC 4 Click driver.
 * @{
 */

/**
 * @defgroup adac4_reg ADAC 4 Registers List
 * @brief List of registers of ADAC 4 Click driver.
 */

/**
 * @addtogroup adac4_reg
 * @{
 */

/**
 * @brief ADAC 4 register list.
 * @details Specified register list of ADAC 4 Click driver.
 */
#define ADAC4_REG_ADC_SEQ               0x02
#define ADAC4_REG_ADC_DAC_CFG           0x03
#define ADAC4_REG_ADC_SEL               0x04
#define ADAC4_REG_DAC_SEL               0x05
#define ADAC4_REG_PULL_DOWN_SEL         0x06
#define ADAC4_REG_LDAC_CTRL             0x07
#define ADAC4_REG_GPIO_WRITE_SEL        0x08
#define ADAC4_REG_GPIO_WRITE_DATA       0x09
#define ADAC4_REG_GPIO_READ_SEL         0x0A
#define ADAC4_REG_POWER_DOWN_CTRL       0x0B
#define ADAC4_REG_OPEN_DRAIN_CFG        0x0C
#define ADAC4_REG_THREE_STATE_SEL       0x0D
#define ADAC4_REG_SW_RESET              0x0F
#define ADAC4_REG_DAC_WRITE             0x10
#define ADAC4_REG_ADC_READ              0x40
#define ADAC4_REG_DAC_READ              0x50
#define ADAC4_REG_GPIO_READ             0x60
#define ADAC4_REG_CHIP_ID               0x7E

/*! @} */ // adac4_reg

/**
 * @defgroup adac4_set ADAC 4 Registers Settings
 * @brief Settings for registers of ADAC 4 Click driver.
 */

/**
 * @addtogroup adac4_set
 * @{
 */

/**
 * @brief ADAC 4 ADC_SEQ register setting.
 * @details Specified setting for ADC_SEQ register of ADAC 4 Click driver.
 */
#define ADAC4_ADC_SEQ_REP_EN            0x0200
#define ADAC4_ADC_SEQ_TEMP_EN           0x0100
#define ADAC4_ADC_SEQ_ADC7_SEL          0x0080
#define ADAC4_ADC_SEQ_ADC6_SEL          0x0040
#define ADAC4_ADC_SEQ_ADC5_SEL          0x0020
#define ADAC4_ADC_SEQ_ADC4_SEL          0x0010
#define ADAC4_ADC_SEQ_ADC3_SEL          0x0008
#define ADAC4_ADC_SEQ_ADC2_SEL          0x0004
#define ADAC4_ADC_SEQ_ADC1_SEL          0x0002
#define ADAC4_ADC_SEQ_ADC0_SEL          0x0001

/**
 * @brief ADAC 4 ADC_DAC_CFG register setting.
 * @details Specified setting for ADC_DAC_CFG register of ADAC 4 Click driver.
 */
#define ADAC4_ADC_DAC_CFG_PRE_CHARGE_EN 0x0200
#define ADAC4_ADC_DAC_CFG_ADC_BUFFER_EN 0x0100
#define ADAC4_ADC_DAC_CFG_GPIO_LOCK     0x0080
#define ADAC4_ADC_DAC_CFG_DAC_WRITE_ALL 0x0040
#define ADAC4_ADC_DAC_CFG_ADC_RANGE_2X  0x0020
#define ADAC4_ADC_DAC_CFG_DAC_RANGE_2X  0x0010

/**
 * @brief ADAC 4 DAC_SEL register setting.
 * @details Specified setting for DAC_SEL register of ADAC 4 Click driver.
 */
#define ADAC4_DAC_SEL_CHANNEL_7         0x0080
#define ADAC4_DAC_SEL_CHANNEL_6         0x0040
#define ADAC4_DAC_SEL_CHANNEL_5         0x0020
#define ADAC4_DAC_SEL_CHANNEL_4         0x0010
#define ADAC4_DAC_SEL_CHANNEL_3         0x0008
#define ADAC4_DAC_SEL_CHANNEL_2         0x0004
#define ADAC4_DAC_SEL_CHANNEL_1         0x0002
#define ADAC4_DAC_SEL_CHANNEL_0         0x0001
#define ADAC4_DAC_SEL_ALL_CHANNELS      0x00FF

/**
 * @brief ADAC 4 DAC_DATA register setting.
 * @details Specified setting for DAC_DATA register of ADAC 4 Click driver.
 */
#define ADAC4_DAC_DATA_MSB              0x8000
#define ADAC4_DAC_DATA_ADDR_MASK        0x7000
#define ADAC4_DAC_DATA_DATA_MASK        0x0FFF
#define ADAC4_DAC_DATA_MIN              0
#define ADAC4_DAC_DATA_MAX              4095

/**
 * @brief ADAC 4 ADC_DATA register setting.
 * @details Specified setting for ADC_DATA register of ADAC 4 Click driver.
 */
#define ADAC4_ADC_DATA_MSB              0x8000
#define ADAC4_ADC_DATA_ADDR_MASK        0x7000
#define ADAC4_ADC_DATA_DATA_MASK        0x0FFF

/**
 * @brief ADAC 4 POWER_DOWN_CTRL register setting.
 * @details Specified setting for POWER_DOWN_CTRL register of ADAC 4 Click driver.
 */
#define ADAC4_POWER_DOWN_CTRL_PD_ALL    0x0400
#define ADAC4_POWER_DOWN_CTRL_EN_REF    0x0200
#define ADAC4_POWER_DOWN_CTRL_PD7       0x0080
#define ADAC4_POWER_DOWN_CTRL_PD6       0x0040
#define ADAC4_POWER_DOWN_CTRL_PD5       0x0020
#define ADAC4_POWER_DOWN_CTRL_PD4       0x0010
#define ADAC4_POWER_DOWN_CTRL_PD3       0x0008
#define ADAC4_POWER_DOWN_CTRL_PD2       0x0004
#define ADAC4_POWER_DOWN_CTRL_PD1       0x0002
#define ADAC4_POWER_DOWN_CTRL_PD0       0x0001

/**
 * @brief ADAC 4 CHIP_ID register setting.
 * @details Specified setting for CHIP_ID register of ADAC 4 Click driver.
 */
#define ADAC4_CHIP_ID                   0x0808

/**
 * @brief ADAC 4 temperature calculation setting.
 * @details Specified setting for temperature calculation of ADAC 4 Click driver.
 */
#define ADAC4_TEMP_OFFSET               1024.0
#define ADAC4_TEMP_RES                  16.0

/**
 * @brief ADAC 4 VREF setting.
 * @details Specified setting for VREF of ADAC 4 Click driver.
 */
#define ADAC4_VREF_INT                  2.5

/**
 * @brief ADAC 4 channel selection setting.
 * @details Specified setting for channel selection of ADAC 4 Click driver.
 */
#define ADAC4_CHANNEL_0                 0
#define ADAC4_CHANNEL_1                 1
#define ADAC4_CHANNEL_2                 2
#define ADAC4_CHANNEL_3                 3
#define ADAC4_CHANNEL_4                 4
#define ADAC4_CHANNEL_5                 5
#define ADAC4_CHANNEL_6                 6
#define ADAC4_CHANNEL_7                 7

/**
 * @brief ADAC 4 device address setting.
 * @details Specified setting for device slave address selection of
 * ADAC 4 Click driver.
 */
#define ADAC4_DEVICE_ADDRESS_0          0x10
#define ADAC4_DEVICE_ADDRESS_1          0x11

/*! @} */ // adac4_set

/**
 * @defgroup adac4_map ADAC 4 MikroBUS Map
 * @brief MikroBUS pin mapping of ADAC 4 Click driver.
 */

/**
 * @addtogroup adac4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADAC 4 Click to the selected MikroBUS.
 */
#define ADAC4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // adac4_map
/*! @} */ // adac4

/**
 * @brief ADAC 4 Click context object.
 * @details Context object definition of ADAC 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float vref;                 /**< Voltage reference. */

} adac4_t;

/**
 * @brief ADAC 4 Click configuration object.
 * @details Configuration object definition of ADAC 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} adac4_cfg_t;

/**
 * @brief ADAC 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADAC4_OK = 0,
    ADAC4_ERROR = -1

} adac4_return_value_t;

/*!
 * @addtogroup adac4 ADAC 4 Click Driver
 * @brief API for configuring and manipulating ADAC 4 Click driver.
 * @{
 */

/**
 * @brief ADAC 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adac4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adac4_cfg_setup ( adac4_cfg_t *cfg );

/**
 * @brief ADAC 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adac4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adac4_init ( adac4_t *ctx, adac4_cfg_t *cfg );

/**
 * @brief ADAC 4 default configuration function.
 * @details This function executes a default configuration of ADAC 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adac4_default_cfg ( adac4_t *ctx );

/**
 * @brief ADAC 4 write register function.
 * @details This function writes a 16-bit value to the specified register.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac4_write_reg ( adac4_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief ADAC 4 read register function.
 * @details This function reads a 16-bit value from the specified register.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac4_read_reg ( adac4_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief ADAC 4 set RST pin state function.
 * @details This function sets the RST pin to the specified logic level.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @param[in] state : Pin logic level (0 or 1).
 * @return None.
 * @note None.
 */
void adac4_set_rst_pin ( adac4_t *ctx, uint8_t state );

/**
 * @brief ADAC 4 hardware reset function.
 * @details This function performs a hardware reset by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void adac4_reset_device ( adac4_t *ctx );

/**
 * @brief ADAC 4 check communication function.
 * @details This function checks communication by verifying the CHIP ID register.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac4_check_communication ( adac4_t *ctx );

/**
 * @brief ADAC 4 write DAC channel function.
 * @details This function writes a value to the specified DAC channel.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @param[in] channel : DAC channel number (0?7).
 * @param[in] dac_data : 12-bit DAC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac4_write_dac ( adac4_t *ctx, uint8_t channel, uint16_t dac_data );

/**
 * @brief ADAC 4 read raw ADC value function.
 * @details This function reads a raw ADC value from the specified channel.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @param[in] channel : ADC channel number (0?7).
 * @param[out] raw_adc : Pointer to memory where raw ADC data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac4_read_raw_adc ( adac4_t *ctx, uint8_t channel, uint16_t *raw_adc );

/**
 * @brief ADAC 4 read ADC voltage function.
 * @details This function reads an ADC voltage value from the specified channel.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @param[in] channel : ADC channel number (0?7).
 * @param[out] voltage : Pointer to memory where voltage in volts will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Requires VREF to be set in the context (internal 2.5V reference by default).
 */
err_t adac4_read_adc_voltage ( adac4_t *ctx, uint8_t channel, float *voltage );

/**
 * @brief ADAC 4 read die temperature function.
 * @details This function reads and calculates internal die temperature.
 * @param[in] ctx : Click context object.
 * See #adac4_t object definition for detailed explanation.
 * @param[out] die_temp : Pointer to memory where temperature in degrees Celsius will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac4_read_die_temp ( adac4_t *ctx, float *die_temp );

#ifdef __cplusplus
}
#endif
#endif // ADAC4_H

/*! @} */ // adac4

// ------------------------------------------------------------------------ END
