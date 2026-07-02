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
 * @file adc28.h
 * @brief This file contains API for ADC 28 Click Driver.
 */

#ifndef ADC28_H
#define ADC28_H

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
 * @addtogroup adc28 ADC 28 Click Driver
 * @brief API for configuring and manipulating ADC 28 Click driver.
 * @{
 */

/**
 * @defgroup adc28_reg ADC 28 Registers List
 * @brief List of registers of ADC 28 Click driver.
 */

/**
 * @addtogroup adc28_reg
 * @{
 */

/**
 * @brief ADC 28 register map.
 * @details Specified register map of ADC 28 Click driver.
 */
#define ADC28_REG_SYSTEM_STATUS             0x00
#define ADC28_REG_GENERAL_CFG               0x01
#define ADC28_REG_DATA_CFG                  0x02
#define ADC28_REG_BUSY_CFG                  0x03
#define ADC28_REG_OPMODE_CFG                0x04
#define ADC28_REG_PIN_CFG                   0x05
#define ADC28_REG_GPO_VALUE                 0x0B
#define ADC28_REG_SEQUENCE_CFG              0x10
#define ADC28_REG_MANUAL_CH_SEL             0x11
#define ADC28_REG_AUTO_SEQ_CH_SEL           0x12
#define ADC28_REG_ALERT_CH_SEL              0x14
#define ADC28_REG_EVENT_FLAG                0x18
#define ADC28_REG_EVENT_HIGH_FLAG           0x1A
#define ADC28_REG_EVENT_LOW_FLAG            0x1C
#define ADC28_REG_EVENT_RGN                 0x1E
#define ADC28_REG_HYSTERESIS_CH0            0x20
#define ADC28_REG_HIGH_TH_CH0               0x21
#define ADC28_REG_EVENT_COUNT_CH0           0x22
#define ADC28_REG_LOW_TH_CH0                0x23
#define ADC28_REG_HYSTERESIS_CH1            0x24
#define ADC28_REG_HIGH_TH_CH1               0x25
#define ADC28_REG_EVENT_COUNT_CH1           0x26
#define ADC28_REG_LOW_TH_CH1                0x27
#define ADC28_REG_HYSTERESIS_CH2            0x28
#define ADC28_REG_HIGH_TH_CH2               0x29
#define ADC28_REG_EVENT_COUNT_CH2           0x2A
#define ADC28_REG_LOW_TH_CH2                0x2B
#define ADC28_REG_HYSTERESIS_CH3            0x2C
#define ADC28_REG_HIGH_TH_CH3               0x2D
#define ADC28_REG_EVENT_COUNT_CH3           0x2E
#define ADC28_REG_LOW_TH_CH3                0x2F
#define ADC28_REG_HYSTERESIS_CH4            0x30
#define ADC28_REG_HIGH_TH_CH4               0x31
#define ADC28_REG_EVENT_COUNT_CH4           0x32
#define ADC28_REG_LOW_TH_CH4                0x33
#define ADC28_REG_HYSTERESIS_CH5            0x34
#define ADC28_REG_HIGH_TH_CH5               0x35
#define ADC28_REG_EVENT_COUNT_CH5           0x36
#define ADC28_REG_LOW_TH_CH5                0x37
#define ADC28_REG_HYSTERESIS_CH6            0x38
#define ADC28_REG_HIGH_TH_CH6               0x39
#define ADC28_REG_EVENT_COUNT_CH6           0x3A
#define ADC28_REG_LOW_TH_CH6                0x3B
#define ADC28_REG_HYSTERESIS_CH7            0x3C
#define ADC28_REG_HIGH_TH_CH7               0x3D
#define ADC28_REG_EVENT_COUNT_CH7           0x3E
#define ADC28_REG_LOW_TH_CH7                0x3F
#define ADC28_REG_RECENT_CH0_LSB            0xA0
#define ADC28_REG_RECENT_CH0_MSB            0xA1
#define ADC28_REG_RECENT_CH1_LSB            0xA2
#define ADC28_REG_RECENT_CH1_MSB            0xA3
#define ADC28_REG_RECENT_CH2_LSB            0xA4
#define ADC28_REG_RECENT_CH2_MSB            0xA5
#define ADC28_REG_RECENT_CH3_LSB            0xA6
#define ADC28_REG_RECENT_CH3_MSB            0xA7
#define ADC28_REG_RECENT_CH4_LSB            0xA8
#define ADC28_REG_RECENT_CH4_MSB            0xA9
#define ADC28_REG_RECENT_CH5_LSB            0xAA
#define ADC28_REG_RECENT_CH5_MSB            0xAB
#define ADC28_REG_RECENT_CH6_LSB            0xAC
#define ADC28_REG_RECENT_CH6_MSB            0xAD
#define ADC28_REG_RECENT_CH7_LSB            0xAE
#define ADC28_REG_RECENT_CH7_MSB            0xAF

/*! @} */ // adc28_reg

/**
 * @defgroup adc28_set ADC 28 Registers Settings
 * @brief Settings for registers of ADC 28 Click driver.
 */

/**
 * @addtogroup adc28_set
 * @{
 */

/**
 * @brief ADC 28 I2C OPCODE commands setting.
 * @details Specified setting for I2C OPCODE commands of ADC 28 Click driver.
 */
#define ADC28_OPCODE_SINGLE_READ            0x10
#define ADC28_OPCODE_SINGLE_WRITE           0x08
#define ADC28_OPCODE_SET_BIT                0x18
#define ADC28_OPCODE_CLEAR_BIT              0x20
#define ADC28_OPCODE_BLOCK_READ             0x30
#define ADC28_OPCODE_BLOCK_WRITE            0x28

/**
 * @brief ADC 28 SYSTEM_STATUS register setting.
 * @details Specified setting for SYSTEM_STATUS register of ADC 28 Click driver.
 */
#define ADC28_SYSTEM_STATUS_BOR             0x01
#define ADC28_SYSTEM_STATUS_I2C_SPEED       0x20
#define ADC28_SYSTEM_STATUS_SEQ_STATUS      0x40

/**
 * @brief ADC 28 GENERAL_CFG register setting.
 * @details Specified setting for GENERAL_CFG register of ADC 28 Click driver.
 */
#define ADC28_GENERAL_CFG_RST               0x01
#define ADC28_GENERAL_CFG_DWC_EN            0x10
#define ADC28_GENERAL_CFG_STATS_EN          0x20

/**
 * @brief ADC 28 DATA_CFG register setting.
 * @details Specified setting for DATA_CFG register of ADC 28 Click driver.
 */
#define ADC28_DATA_CFG_APPEND_STATUS_NONE   0x00
#define ADC28_DATA_CFG_APPEND_STATUS_CHID   0x10
#define ADC28_DATA_CFG_APPEND_STATUS_ALERT  0x20
#define ADC28_DATA_CFG_FIX_PAT              0x80

/**
 * @brief ADC 28 BUSY_CFG register setting.
 * @details Specified setting for BUSY_CFG register of ADC 28 Click driver.
 */
#define ADC28_BUSY_CFG_BUSYTIME_1_2US       0x00
#define ADC28_BUSY_CFG_BUSYTIME_6_0US       0xC0

/**
 * @brief ADC 28 OPMODE_CFG register setting.
 * @details Specified setting for OPMODE_CFG register of ADC 28 Click driver.
 */
#define ADC28_OPMODE_CFG_CLK_DIV_0_75MS     0x00
#define ADC28_OPMODE_CFG_CLK_DIV_1_5MS      0x01
#define ADC28_OPMODE_CFG_CLK_DIV_3MS        0x02
#define ADC28_OPMODE_CFG_CLK_DIV_6MS        0x03
#define ADC28_OPMODE_CFG_CONV_MODE_MANUAL   0x00
#define ADC28_OPMODE_CFG_CONV_MODE_AUTO     0x20

/**
 * @brief ADC 28 SEQUENCE_CFG register setting.
 * @details Specified setting for SEQUENCE_CFG register of ADC 28 Click driver.
 */
#define ADC28_SEQUENCE_CFG_SEQ_MODE_MANUAL  0x00
#define ADC28_SEQUENCE_CFG_SEQ_MODE_AUTO    0x01
#define ADC28_SEQUENCE_CFG_SEQ_START        0x10

/**
 * @brief ADC 28 channel selection setting.
 * @details Specified setting for channel selection of ADC 28 Click driver.
 */
#define ADC28_CHANNEL_0                     0x00
#define ADC28_CHANNEL_1                     0x01
#define ADC28_CHANNEL_2                     0x02
#define ADC28_CHANNEL_3                     0x03
#define ADC28_CHANNEL_4                     0x04
#define ADC28_CHANNEL_5                     0x05
#define ADC28_CHANNEL_6                     0x06
#define ADC28_CHANNEL_7                     0x07
#define ADC28_CHANNEL_MASK                  0x0F

/**
 * @brief ADC 28 AUTO_SEQ_CH_SEL bitmask setting.
 * @details Specified setting for AUTO_SEQ_CH_SEL bitmask of ADC 28 Click driver.
 */
#define ADC28_AUTO_SEQ_CH0                  0x01
#define ADC28_AUTO_SEQ_CH1                  0x02
#define ADC28_AUTO_SEQ_CH2                  0x04
#define ADC28_AUTO_SEQ_CH3                  0x08
#define ADC28_AUTO_SEQ_CH4                  0x10
#define ADC28_AUTO_SEQ_CH5                  0x20
#define ADC28_AUTO_SEQ_CH6                  0x40
#define ADC28_AUTO_SEQ_CH7                  0x80
#define ADC28_AUTO_SEQ_ALL_CH               0xFF

/**
 * @brief ADC 28 data resolution and VDD setting.
 * @details Specified setting for data resolution and VDD of ADC 28 Click driver.
 */
#define ADC28_ADC_RESOLUTION                4096.0f
#define ADC28_VDD_3V3                       3.3f
#define ADC28_VDD_5V                        5.0f

/**
 * @brief ADC 28 data threshold, hysteresis and even count setting.
 * @details Specified setting for threshold, hysteresis and event count of ADC 28 Click driver.
 */
#define ADC28_THRESHOLD_LIMIT               0x0FFF
#define ADC28_HYSTERESIS_LIMIT              0x0F
#define ADC28_EVENT_COUNT_LIMIT             0x0F
#define ADC28_HYSTERESIS_MASK               0x0F
#define ADC28_EVENT_COUNT_MASK              0x0F
#define ADC28_HIGH_THR_MSB_MASK             0xFF
#define ADC28_LOW_THR_MSB_MASK              0xFF
#define ADC28_HIGH_THR_LSB_MASK             0xF0
#define ADC28_LOW_THR_LSB_MASK              0xF0
#define ADC28_4_LSB_MASK                    0x000F

/**
 * @brief ADC 28 device address setting.
 * @details Specified setting for device slave address selection of
 * ADC 28 Click driver.
 */
#define ADC28_DEVICE_ADDR_R1_0_R2_OPEN      0x17
#define ADC28_DEVICE_ADDR_R1_100K_R2_OPEN   0x14
#define ADC28_DEVICE_ADDR_R1_OPEN_R2_0      0x10
#define ADC28_DEVICE_ADDR_R1_OPEN_R2_100K   0x13
#define ADC28_DEVICE_ADDRESS                ADC28_DEVICE_ADDR_R1_0_R2_OPEN

/*! @} */ // adc28_set

/**
 * @defgroup adc28_map ADC 28 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 28 Click driver.
 */

/**
 * @addtogroup adc28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 28 Click to the selected MikroBUS.
 */
#define ADC28_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc28_map
/*! @} */ // adc28

/**
 * @brief ADC 28 Click context object.
 * @details Context object definition of ADC 28 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alt;           /**< Alert interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    // Supply voltage
    float vdd;                  /**< Supply voltage in volts (3.3 or 5.0). */

} adc28_t;

/**
 * @brief ADC 28 Click configuration object.
 * @details Configuration object definition of ADC 28 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alt;             /**< Alert interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} adc28_cfg_t;

/**
 * @brief ADC 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC28_OK = 0,
    ADC28_ERROR = -1

} adc28_return_value_t;

/*!
 * @addtogroup adc28 ADC 28 Click Driver
 * @brief API for configuring and manipulating ADC 28 Click driver.
 * @{
 */

/**
 * @brief ADC 28 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc28_cfg_setup ( adc28_cfg_t *cfg );

/**
 * @brief ADC 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_init ( adc28_t *ctx, adc28_cfg_t *cfg );

/**
 * @brief ADC 28 default configuration function.
 * @details This function executes a default configuration of ADC 28
 * Click board.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc28_default_cfg ( adc28_t *ctx );

/**
 * @brief ADC 28 write register function.
 * @details This function writes a desired data word to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_write_reg ( adc28_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ADC 28 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_write_regs ( adc28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ADC 28 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_read_reg ( adc28_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ADC 28 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_read_regs ( adc28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ADC 28 get alert pin function.
 * @details This function returns the logic state of the ALT (ALERT) pin.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t adc28_get_alert_pin ( adc28_t *ctx );

/**
 * @brief ADC 28 set high threshold function.
 * @details This function sets the high threshold for the selected channel.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] channel : Channel selection.
 * @param[in] high_th : High threshold 12-bit raw ADC value [0, 4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_set_high_threshold ( adc28_t *ctx, uint8_t channel, uint16_t high_th );

/**
 * @brief ADC 28 set low threshold function.
 * @details This function sets the low threshold for the selected channel.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] channel : Channel selection.
 * @param[in] low_th : Low threshold 12-bit raw ADC value [0, 4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_set_low_threshold ( adc28_t *ctx, uint8_t channel, uint16_t low_th );

/**
 * @brief ADC 28 set hysteresis function.
 * @details This function sets the hysteresis for the selected channel.
 * The actual hysteresis applied by the device is the written value multiplied by 8 LSBs.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] channel : Channel selection.
 * @param[in] hysteresis : Hysteresis value [0, 15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_set_hysteresis ( adc28_t *ctx, uint8_t channel, uint8_t hysteresis );

/**
 * @brief ADC 28 set event count function.
 * @details This function sets the number of consecutive threshold crossings
 * required before the ALERT flag is set for the selected channel.
 * ALERT triggers after event_count + 1 crossings.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] channel : Channel selection.
 * @param[in] event_count : Event count value [0, 15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_set_event_count ( adc28_t *ctx, uint8_t channel, uint8_t event_count );

/**
 * @brief ADC 28 read raw ADC function.
 * @details This function reads the RAW ADC measurement.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] channel : Channel selection.
 * @param[out] raw_data : Pointer to the raw ADC result [0, 4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_read_raw_adc ( adc28_t *ctx, uint8_t channel, uint16_t *raw_data );

/**
 * @brief ADC 28 read voltage function.
 * @details This function reads the ADC result from the selected channel and
 * converts it to a voltage level.
 * @param[in] ctx : Click context object.
 * See #adc28_t object definition for detailed explanation.
 * @param[in] channel : Channel selection.
 * @param[out] voltage : Pointer to the output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc28_read_voltage ( adc28_t *ctx, uint8_t channel, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // ADC28_H

/*! @} */ // adc28

// ------------------------------------------------------------------------ END
