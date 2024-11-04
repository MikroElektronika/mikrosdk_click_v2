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
 * @file adc16.h
 * @brief This file contains API for ADC 16 Click Driver.
 */

#ifndef ADC16_H
#define ADC16_H

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
 * @addtogroup adc16 ADC 16 Click Driver
 * @brief API for configuring and manipulating ADC 16 Click driver.
 * @{
 */

/**
 * @defgroup adc16_reg ADC 16 Registers List
 * @brief List of registers of ADC 16 Click driver.
 */

/**
 * @addtogroup adc16_reg
 * @{
 */

/**
 * @brief ADC 16 Opcodes for Commands.
 * @details Specified Opcodes for Commands of ADC 16 Click driver.
 */
#define ADC16_OPCODE_SINGLE_READ                    0x10
#define ADC16_OPCODE_SINGLE_WRITE                   0x08
#define ADC16_OPCODE_SET_BIT                        0x18
#define ADC16_OPCODE_CLEAR_BIT                      0x20
#define ADC16_OPCODE_CONTINUOUS_READ                0x30
#define ADC16_OPCODE_CONTINUOUS_WRITE               0x28

/**
 * @brief ADC 16 Register Map.
 * @details Specified Register Map of ADC 16 Click driver.
 */
#define ADC16_REG_OPMODE_I2CMODE_STATUS             0x00
#define ADC16_REG_DATA_BUFFER_STATUS                0x01
#define ADC16_REG_ACCUMULATOR_STATUS                0x02
#define ADC16_REG_ALERT_TRIG_CHID                   0x03
#define ADC16_REG_SEQUENCE_STATUS                   0x04
#define ADC16_REG_ACC_CH0_LSB                       0x08
#define ADC16_REG_ACC_CH0_MSB                       0x09
#define ADC16_REG_ACC_CH1_LSB                       0x0A
#define ADC16_REG_ACC_CH1_MSB                       0x0B
#define ADC16_REG_ALERT_LOW_FLAGS                   0x0C
#define ADC16_REG_ALERT_HIGH_FLAGS                  0x0E
#define ADC16_REG_DEVICE_RESET                      0x14
#define ADC16_REG_OFFSET_CAL                        0x15
#define ADC16_REG_WKEY                              0x17
#define ADC16_REG_OSC_SEL                           0x18
#define ADC16_REG_NCLK_SEL                          0x19
#define ADC16_REG_OPMODE_SEL                        0x1C
#define ADC16_REG_START_SEQUENCE                    0x1E
#define ADC16_REG_ABORT_SEQUENCE                    0x1F
#define ADC16_REG_AUTO_SEQ_CHEN                     0x20
#define ADC16_REG_CH_INPUT_CFG                      0x24
#define ADC16_REG_DOUT_FORMAT_CFG                   0x28
#define ADC16_REG_DATA_BUFFER_OPMODE                0x2C
#define ADC16_REG_ACC_EN                            0x30
#define ADC16_REG_ALERT_CHEN                        0x34
#define ADC16_REG_PRE_ALT_MAX_EVENT_COUNT           0x36
#define ADC16_REG_ALERT_DWC_EN                      0x37
#define ADC16_REG_DWC_HTH_CH0_LSB                   0x38
#define ADC16_REG_DWC_HTH_CH0_MSB                   0x39
#define ADC16_REG_DWC_LTH_CH0_LSB                   0x3A
#define ADC16_REG_DWC_LTH_CH0_MSB                   0x3B
#define ADC16_REG_DWC_HTH_CH1_LSB                   0x3C
#define ADC16_REG_DWC_HTH_CH1_MSB                   0x3D
#define ADC16_REG_DWC_LTH_CH1_LSB                   0x3E
#define ADC16_REG_DWC_LTH_CH1_MSB                   0x3F
#define ADC16_REG_DWC_HYS_CH0                       0x40
#define ADC16_REG_DWC_HYS_CH1                       0x41

/*! @} */ // adc16_reg

/**
 * @defgroup adc16_set ADC 16 Registers Settings
 * @brief Settings for registers of ADC 16 Click driver.
 */

/**
 * @addtogroup adc16_set
 * @{
 */

/**
 * @brief ADC 16 WKEY values.
 * @details Specified WKEY values of ADC 16 Click driver.
 */
#define ADC16_WKEY_UNLOCK                           0x0A
#define ADC16_WKEY_LOCK                             0x00

/**
 * @brief ADC 16 device reset value.
 * @details Specified device reset value of ADC 16 Click driver.
 */
#define ADC16_DEVICE_RESET                          0x01

/**
 * @brief ADC 16 start calibration value.
 * @details Specified start calibration value of ADC 16 Click driver.
 */
#define ADC16_START_CALIBRATION                     0x01

/**
 * @brief ADC 16 channel input config values.
 * @details Specified channel input config values of ADC 16 Click driver.
 */
#define ADC16_CH_CFG_TWO_CH_SINGLE_END              0x00
#define ADC16_CH_CFG_SIN_CH_SINGLE_END_RMT_GND      0x01
#define ADC16_CH_CFG_SIN_CH_SINGLE_END_PSEUDO_DIFF  0x02

/**
 * @brief ADC 16 opmode sel values.
 * @details Specified opmode sel values of ADC 16 Click driver.
 */
#define ADC16_OPMODE_SEL_MAN_WITH_CH0               0x00
#define ADC16_OPMODE_SEL_MAN_WITH_AUTO_SEQ          0x04
#define ADC16_OPMODE_SEL_AUTO_WITH_AUTO_SEQ         0x06
#define ADC16_OPMODE_SEL_HIGH_PREC_WITH_AUTO_SEQ    0x07

/**
 * @brief ADC 16 auto sequence channel enable values.
 * @details Specified auto sequence channel enable values of ADC 16 Click driver.
 */
#define ADC16_AUTOSEQ_EN_CH0                        0x01
#define ADC16_AUTOSEQ_EN_CH1                        0x02
#define ADC16_AUTOSEQ_EN_BOTH_CH                    0x03

/**
 * @brief ADC 16 start and abort sequence values.
 * @details Specified start and abort sequence values of ADC 16 Click driver.
 */
#define ADC16_START_SEQUENCE                        0x01
#define ADC16_ABORT_SEQUENCE                        0x01

/**
 * @brief ADC 16 calculation values.
 * @details Specified calculation values of ADC 16 Click driver.
 */
#define ADC16_RESOLUTION                            0x0FFF
#define ADC16_VREF                                  3.3

/**
 * @brief ADC 16 device address setting.
 * @details Specified setting for device slave address selection of
 * ADC 16 Click driver.
 */
#define ADC16_DEV_ADDR_R1_0_R2_DNP                  0x1F
#define ADC16_DEV_ADDR_R1_11K_R2_DNP                0x1E
#define ADC16_DEV_ADDR_R1_33K_R2_DNP                0x1D
#define ADC16_DEV_ADDR_R1_100K_R2_DNP               0x1C
#define ADC16_DEV_ADDR_R1_DNP_R2_DNP                0x18
#define ADC16_DEV_ADDR_R1_DNP_R2_11K                0x19
#define ADC16_DEV_ADDR_R1_DNP_R2_33K                0x1A
#define ADC16_DEV_ADDR_R1_DNP_R2_100K               0x1B

/*! @} */ // adc16_set

/**
 * @defgroup adc16_map ADC 16 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 16 Click driver.
 */

/**
 * @addtogroup adc16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 16 Click to the selected MikroBUS.
 */
#define ADC16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc16_map
/*! @} */ // adc16

/**
 * @brief ADC 16 Click context object.
 * @details Context object definition of ADC 16 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  rdy;          /**< Ready pin indicator. */
    digital_in_t  alr;          /**< Alert pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} adc16_t;

/**
 * @brief ADC 16 Click configuration object.
 * @details Configuration object definition of ADC 16 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rdy;            /**< Ready pin indicator. */
    pin_name_t  alr;            /**< Alert pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} adc16_cfg_t;

/**
 * @brief ADC 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC16_OK = 0,
    ADC16_ERROR = -1

} adc16_return_value_t;

/*!
 * @addtogroup adc16 ADC 16 Click Driver
 * @brief API for configuring and manipulating ADC 16 Click driver.
 * @{
 */

/**
 * @brief ADC 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc16_cfg_setup ( adc16_cfg_t *cfg );

/**
 * @brief ADC 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc16_init ( adc16_t *ctx, adc16_cfg_t *cfg );

/**
 * @brief ADC 16 default configuration function.
 * @details This function executes a default configuration of ADC 16
 * Click board.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc16_default_cfg ( adc16_t *ctx );

/**
 * @brief ADC 16 single register write function.
 * @details This function writes a single data to the selected register.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc16_single_register_write ( adc16_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ADC 16 single register read function.
 * @details This function reads a single data from the selected register.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Data read from register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc16_single_register_read ( adc16_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ADC 16 set register bits function.
 * @details This function sets desired bits of the selected register. Bits with value as 1 in
 * register data are set and bits with value as 0 in register data are not changed.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] bit_mask : Bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc16_set_register_bits ( adc16_t *ctx, uint8_t reg, uint8_t bit_mask );

/**
 * @brief ADC 16 clear register bits function.
 * @details This function clears desired bits of the selected register. Bits with value as 1 in
 * register data are cleared and bits with value as 0 in register data are not changed.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] bit_mask : Bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc16_clear_register_bits ( adc16_t *ctx, uint8_t reg, uint8_t bit_mask );

/**
 * @brief ADC 16 continuous register write function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc16_continuous_register_write ( adc16_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief ADC 16 continuous register read function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc16_continuous_register_read ( adc16_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief ADC 16 get rdy pin function.
 * @details This function returns the RDY pin logic state.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @return Pin logic level.
 * @note None.
 */
uint8_t adc16_get_rdy_pin ( adc16_t *ctx );

/**
 * @brief ADC 16 get alr pin function.
 * @details This function returns the ALR pin logic state.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @return Pin logic level.
 * @note None.
 */
uint8_t adc16_get_alr_pin ( adc16_t *ctx );

/**
 * @brief ADC 16 get voltage function.
 * @details This function reads the voltage from two analog input single-ended channels.
 * @param[in] ctx : Click context object.
 * See #adc16_t object definition for detailed explanation.
 * @param[out] ain0_voltage : AIN0 voltage value [V].
 * @param[out] ain1_voltage : AIN1 voltage value [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc16_get_voltage ( adc16_t *ctx, float *ain0_voltage, float *ain1_voltage );

#ifdef __cplusplus
}
#endif
#endif // ADC16_H

/*! @} */ // adc16

// ------------------------------------------------------------------------ END
