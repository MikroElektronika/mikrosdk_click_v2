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
 * @file pac1944.h
 * @brief This file contains API for PAC1944 Click Driver.
 */

#ifndef PAC1944_H
#define PAC1944_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup pac1944 PAC1944 Click Driver
 * @brief API for configuring and manipulating PAC1944 Click driver.
 * @{
 */

/**
 * @defgroup pac1944_reg PAC1944 Registers List
 * @brief List of registers of PAC1944 Click driver.
 */

/**
 * @addtogroup pac1944_reg
 * @{
 */

/**
 * @brief PAC1944 description register.
 * @details Specified register for description of PAC1944 Click driver.
 */

#define PAC1944_REG_REFRESH                           0x00
#define PAC1944_REG_CTRL                              0x01
#define PAC1944_REG_ACC_COUNT                         0x02
#define PAC1944_REG_VACC_CH1                          0x03
#define PAC1944_REG_VACC_CH2                          0x04
#define PAC1944_REG_VACC_CH3                          0x05
#define PAC1944_REG_VACC_CH4                          0x06
#define PAC1944_REG_VBUS_CH1                          0x07
#define PAC1944_REG_VBUS_CH2                          0x08
#define PAC1944_REG_VBUS_CH3                          0x09
#define PAC1944_REG_VBUS_CH4                          0x0A
#define PAC1944_REG_VSENSE_CH1                        0x0B
#define PAC1944_REG_VSENSE_CH2                        0x0C
#define PAC1944_REG_VSENSE_CH3                        0x0D
#define PAC1944_REG_VSENSE_CH4                        0x0E
#define PAC1944_REG_VBUS_CH1_AVG                      0x0F
#define PAC1944_REG_VBUS_CH2_AVG                      0x10
#define PAC1944_REG_VBUS_CH3_AVG                      0x11
#define PAC1944_REG_VBUS_CH4_AVG                      0x12
#define PAC1944_REG_VSENSE_CH1_AVG                    0x13
#define PAC1944_REG_VSENSE_CH2_AVG                    0x14
#define PAC1944_REG_VSENSE_CH3_AVG                    0x15
#define PAC1944_REG_VSENSE_CH4_AVG                    0x16
#define PAC1944_REG_VPOWER_CH1                        0x17
#define PAC1944_REG_VPOWER_CH2                        0x18
#define PAC1944_REG_VPOWER_CH3                        0x19
#define PAC1944_REG_VPOWER_CH4                        0x1A
#define PAC1944_REG_SMBUS_CFG                         0x1C
#define PAC1944_REG_NEG_PWR_FSR                       0x1D
#define PAC1944_REG_REFRESH_G                         0x1E
#define PAC1944_REG_REFRESH_V                         0x1F
#define PAC1944_REG_SLOW                              0x20
#define PAC1944_REG_CTRL_ACT                          0x21
#define PAC1944_REG_NEG_PWR_FSR_ACT                   0x22
#define PAC1944_REG_CTRL_LAT                          0x23
#define PAC1944_REG_NEG_PWR_FSR_LAT                   0x24
#define PAC1944_REG_ACC_CFG                           0x25
#define PAC1944_REG_ALERT_STATUS                      0x26
#define PAC1944_REG_SLOW_ALERT1                       0x27
#define PAC1944_REG_GPIO_ALERT2                       0x28
#define PAC1944_REG_ACC_FULLNESS_LIM                  0x29
#define PAC1944_REG_OC_LIM_CH1                        0x30
#define PAC1944_REG_OC_LIM_CH2                        0x31
#define PAC1944_REG_OC_LIM_CH3                        0x32
#define PAC1944_REG_OC_LIM_CH4                        0x33
#define PAC1944_REG_UC_LIM_CH1                        0x34
#define PAC1944_REG_UC_LIM_CH2                        0x35
#define PAC1944_REG_UC_LIM_CH3                        0x36
#define PAC1944_REG_UC_LIM_CH4                        0x37
#define PAC1944_REG_OP_LIM_CH1                        0x38
#define PAC1944_REG_OP_LIM_CH2                        0x39
#define PAC1944_REG_OP_LIM_CH3                        0x3A
#define PAC1944_REG_OP_LIM_CH4                        0x3B
#define PAC1944_REG_OV_LIM_CH1                        0x3C
#define PAC1944_REG_OV_LIM_CH2                        0x3D
#define PAC1944_REG_OV_LIM_CH3                        0x3E
#define PAC1944_REG_OV_LIM_CH4                        0x3F
#define PAC1944_REG_UV_LIM_CH1                        0x40
#define PAC1944_REG_UV_LIM_CH2                        0x41
#define PAC1944_REG_UV_LIM_CH3                        0x42
#define PAC1944_REG_UV_LIM_CH4                        0x43
#define PAC1944_REG_OC_LIM_NSAMPLES                   0x44
#define PAC1944_REG_UC_LIM_NSAMPLES                   0x45
#define PAC1944_REG_OP_LIM_NSAMPLES                   0x46
#define PAC1944_REG_OV_LIM_NSAMPLES                   0x47
#define PAC1944_REG_UV_LIM_NSAMPLES                   0x48
#define PAC1944_REG_ALERT_ENABLE                      0x49
#define PAC1944_REG_ACC_CFG_ACT                       0x4A
#define PAC1944_REG_ACC_CFG_LAT                       0x4B
#define PAC1944_REG_ID_PRODUCT                        0xFD
#define PAC1944_REG_ID_MANUFACTURER                   0xFE
#define PAC1944_REG_ID_REVISION                       0xFF

/*! @} */ // pac1944_reg

/**
 * @addtogroup meas_sel
 * @{
 */

/**
 * @brief PAC1944 Measurement selection.
 * @details Selection for measurement data of the PAC1944 Click driver.
 */

#define PAC1944_MEAS_SEL_V_SOURCE                     0
#define PAC1944_MEAS_SEL_I_SENSE                      1
#define PAC1944_MEAS_SEL_P_SENSE                      2

/*! @} */ // meas_sel

/**
 * @addtogroup ch_sel
 * @{
 */

/**
 * @brief PAC1944 Channel selection.
 * @details Channel selection for measurement data output of the PAC1944 Click driver.
 */

#define PAC1944_CH_SEL_CH_1                           1
#define PAC1944_CH_SEL_CH_2                           2
#define PAC1944_CH_SEL_CH_3                           3
#define PAC1944_CH_SEL_CH_4                           4

/*! @} */ // ch_sel

/**
 * @addtogroup avg_sel
 * @{
 */

/**
 * @brief PAC1944 Averaging mode selection.
 * @details Averaging mode selection for measurement data output of the PAC1944 Click driver.
 */

#define PAC1944_AVG_SEL_DISABLE                       0
#define PAC1944_AVG_SEL_ENABLE                        1

/*! @} */ // avg_sel

/**
 * @addtogroup meas_mode
 * @{
 */

/**
 * @brief PAC1944 Measure mode selection.
 * @details Measure mode selection for measurement data output of the PAC1944 Click driver.
 */

#define PAC1944_MEAS_MODE_UNIPOLAR_FSR                0
#define PAC1944_MEAS_MODE_BIPOLAR_FSR                 1
#define PAC1944_MEAS_MODE_BIPOLAR_HALF_FSR            2

/*! @} */ // meas_mode

/**
 * @addtogroup state
 * @{
 */

/**
 * @brief PAC1944 Pin states.
 * @details Measure mode selection for measurement data output of the PAC1944 Click driver.
 */

#define PAC1944_SLOW_STATE_ON                         1
#define PAC1944_SLOW_STATE_OFF                        0

#define PAC1944_DEV_ENABLE                            1
#define PAC1944_DEV_PWR_DWN                           0

#define PAC1944_ALERT_ACTIVE                          0
#define PAC1944_ALERT_INACTIVE                        1

/*! @} */ // state

/**
 * @defgroup pac1944_set PAC1944 Registers Settings
 * @brief Settings for registers of PAC1944 Click driver.
 */

/**
 * @addtogroup pac1944_set
 * @{
 */

/**
 * @brief PAC1944 description setting.
 * @details Specified setting for description of PAC1944 Click driver.
 */

#define PAC1944_CTRLH_SPS_1024_ADAPT_ACC              0x00
#define PAC1944_CTRLH_SPS_256_ADAPT_ACC               0x10
#define PAC1944_CTRLH_SPS_64_ADAPT_ACC                0x20
#define PAC1944_CTRLH_SPS_8_ADAPT_ACC                 0x30
#define PAC1944_CTRLH_SPS_1024                        0x40
#define PAC1944_CTRLH_SPS_256                         0x50
#define PAC1944_CTRLH_SPS_64                          0x60
#define PAC1944_CTRLH_SPS_8                           0x70
#define PAC1944_CTRLH_SINGLE_SHOT_MODE                0x80
#define PAC1944_CTRLH_SINGLE_SHOT_8X                  0x90
#define PAC1944_CTRLH_FAST_MODE                       0xA0
#define PAC1944_CTRLH_BURST_MODE                      0xB0
#define PAC1944_CTRLH_SLEEP                           0xF0
    
#define PAC1944_CTRLH_INT_PIN_ALERT                   0x00
#define PAC1944_CTRLH_INT_PIN_DIG_IN                  0x04
#define PAC1944_CTRLH_INT_PIN_DIG_OUT                 0x08
#define PAC1944_CTRLH_INT_PIN_SLOW                    0x0C
    
#define PAC1944_CTRLH_SLW_PIN_ALERT                   0x00
#define PAC1944_CTRLH_SLW_PIN_DIG_IN                  0x01
#define PAC1944_CTRLH_SLW_PIN_DIG_OUT                 0x02
#define PAC1944_CTRLH_SLW_PIN_SLOW                    0x03

#define PAC1944_CTRLL_CH1_OFF                         0x80
#define PAC1944_CTRLL_CH2_OFF                         0x40
#define PAC1944_CTRLL_CH3_OFF                         0x20
#define PAC1944_CTRLL_CH4_OFF                         0x10
#define PAC1944_CTRLL_ALL_CH_OFF                      0xF0
#define PAC1944_CTRLL_ALL_CH_ON                       0x00

#define PAC1944_SMBUS_INT_PIN_MASK                    0x80
#define PAC1944_SMBUS_SLW_PIN_MASK                    0x40
#define PAC1944_SMBUS_ALERT_MASK                      0x20
#define PAC1944_SMBUS_POR_MASK                        0x10
#define PAC1944_SMBUS_TIMEOUT_OFF                     0x00
#define PAC1944_SMBUS_TIMEOUT_ON                      0x08
#define PAC1944_SMBUS_BYTE_COUNT_OFF                  0x00
#define PAC1944_SMBUS_BYTE_COUNT_ON                   0x04
#define PAC1944_SMBUS_AUTO_INC_SKIP_ON                0x00
#define PAC1944_SMBUS_AUTO_INC_SKIP_OFF               0x02
#define PAC1944_SMBUS_I2C_HIGH_SPEED                  0x01

/**
 * @brief PAC1944 device address setting.
 * @details Specified setting for device slave address selection of
 * PAC1944 Click driver.
 */

#define PAC1944_DEVICE_ADDR_GND                       0x10
#define PAC1944_DEVICE_ADDR_499_OHM                   0x11
#define PAC1944_DEVICE_ADDR_806_OHM                   0x12
#define PAC1944_DEVICE_ADDR_1270_OHM                  0x13
#define PAC1944_DEVICE_ADDR_2050_OHM                  0x14
#define PAC1944_DEVICE_ADDR_3240_OHM                  0x15
#define PAC1944_DEVICE_ADDR_5230_OHM                  0x16
#define PAC1944_DEVICE_ADDR_8450_OHM                  0x17
#define PAC1944_DEVICE_ADDR_13K3_OHM                  0x18
#define PAC1944_DEVICE_ADDR_21K5_OHM                  0x19
#define PAC1944_DEVICE_ADDR_34K_OHM                   0x1A
#define PAC1944_DEVICE_ADDR_54K9_OHM                  0x1B
#define PAC1944_DEVICE_ADDR_88K7_OHM                  0x1C
#define PAC1944_DEVICE_ADDR_140K_OHM                  0x1D
#define PAC1944_DEVICE_ADDR_226K_OHM                  0x1E
#define PAC1944_DEVICE_ADDR_VCC                       0x1F

/*! @} */ // pac1944_set

/**
 * @defgroup pac1944_map PAC1944 MikroBUS Map
 * @brief MikroBUS pin mapping of PAC1944 Click driver.
 */

/**
 * @addtogroup pac1944_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PAC1944 Click to the selected MikroBUS.
 */
#define PAC1944_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.slw = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pac1944_map
/*! @} */ // pac1944

/**
 * @brief PAC1944 Click context object.
 * @details Context object definition of PAC1944 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  en;                               /**< Output device enable pin. */
    digital_out_t  slw;                              /**< Output slow sampling state pin. */

    // Input pins

    digital_in_t   int_pin;                          /**< Input interrupt pin. */

    // Modules

    i2c_master_t   i2c;                              /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} pac1944_t;

/**
 * @brief PAC1944 Click configuration object.
 * @details Configuration object definition of PAC1944 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;                                  /**< Output device enable pin. */
    pin_name_t  slw;                                 /**< Output slow sampling state pin. */
    pin_name_t  int_pin;                             /**< Input interrupt pin. */

    uint32_t  i2c_speed;                             /**< I2C serial speed. */
    uint8_t   i2c_address;                           /**< I2C slave address. */

} pac1944_cfg_t;

/**
 * @brief PAC1944 Configuration setup structure.
 * @details Configuration setup of PAC1944 Click driver.
 */
typedef struct
{
    uint8_t sample_mode;                             /**< SAMPLE_MODE bits CTRL[15:12] reg. */
    uint8_t gpio_alert2;                             /**< GPIO_ALERT2 bits CTRL[11:10] reg. */
    uint8_t slow_alert1;                             /**< SLOW_ALERT1 bits CTRL[9:8] reg. */
    uint8_t channels_state;                          /**< Channel N OFF bits CTRL[7:4] reg. */
    uint8_t cfg_vsense1;                             /**< Configure Channel 1 FSR for Vsense measurements. */
    uint8_t cfg_vsense2;                             /**< Configure Channel 2 FSR for Vsense measurements. */
    uint8_t cfg_vsense3;                             /**< Configure Channel 3 FSR for Vsense measurements. */
    uint8_t cfg_vsense4;                             /**< Configure Channel 4 FSR for Vsense measurements. */
    uint8_t cfg_vbus1;                               /**< Configure Channel 1 FSR for Vbus measurements. */
    uint8_t cfg_vbus2;                               /**< Configure Channel 2 FSR for Vbus measurements. */
    uint8_t cfg_vbus3;                               /**< Configure Channel 3 FSR for Vbus measurements. */
    uint8_t cfg_vbus4;                               /**< Configure Channel 4 FSR for Vbus measurements. */
    
} pac1944_setup_t;

/*!
 * @addtogroup pac1944 PAC1944 Click Driver
 * @brief API for configuring and manipulating PAC1944 Click driver.
 * @{
 */

/**
 * @brief PAC1944 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pac1944_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void pac1944_cfg_setup ( pac1944_cfg_t *cfg );

/**
 * @brief PAC1944 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pac1944_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t pac1944_init ( pac1944_t *ctx, pac1944_cfg_t *cfg );

/**
 * @brief PAC1944 default configuration function.
 * @details This function executes a default configuration of PAC1944
 * click board.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 *
 * @note Default config enables all channels. Channel 1 is set to work 
 * in bipolar full scale range mode. Channel 2 is set to bipolar half
 * scale range mode. Channels 3 and 4 are configured to unipolar
 * full scale range mode. Sampling frequency is set to 1024 SPS
 * and pin configuration for PAC1944 are default.
 *
 * @endcode
 */
void pac1944_default_cfg ( pac1944_t *ctx );

/**
 * @brief PAC1944 set slow state function.
 * @details This function sets the state of slw pin.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 *     @li @c 0 ( PAC1944_SLOW_STATE_OFF ) - Disables the 8 sps sampling on all channels,
 *     @li @c 1 ( PAC1944_SLOW_STATE_ON ) - Enables the 8 sps sampling on all channels.
 *
 * @note None.
 *
 * @endcode
 */
void pac1944_set_slow_state ( pac1944_t *ctx, uint8_t state );

/**
 * @brief PAC1944 set device state function.
 * @details This function sets the state of en pin.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 *     @li @c 0 ( PAC1944_DEV_PWR_DWN ) - Sets the PAC1944 in power down mode,
 *     @li @c 1 ( PAC1944_DEV_ENABLE ) - Sets the PAC1944 in normal operating mode.
 *
 * @note None.
 *
 * @endcode
 */
void pac1944_device_state ( pac1944_t *ctx, uint8_t state );

/**
 * @brief PAC1944 get alert state function.
 * @details This function checks the state of int pin.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @return @li @c 0 ( PAC1944_ALERT_ACTIVE ) - Alert triggered,
 *         @li @c 1 ( PAC1944_ALERT_INACTIVE ) - Alert on standby.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t pac1944_get_alert_state ( pac1944_t *ctx );

/**
 * @brief PAC1944 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
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
err_t pac1944_generic_write ( pac1944_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief PAC1944 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
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
err_t pac1944_generic_read ( pac1944_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief PAC1944 setup config function.
 * @details This function checks the state of int pin.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @param[in] cfg_data : Configuration for setup of the device.
 *
 * @note None.
 *
 * @endcode
 */
void pac1944_setup_config ( pac1944_t *ctx, pac1944_setup_t cfg_data );

/**
 * @brief PAC1944 set address pointer function.
 * @details This function allows user to set the internal address pointer on
 * the desired register.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @param[in] reg_addr : Targeted register address.
 *
 * @note None.
 *
 * @endcode
 */
void pac1944_set_address_pointer ( pac1944_t *ctx, uint8_t reg_addr );

/**
 * @brief PAC1944 last accessed register read function.
 * @details This function allows user to read the last accessed register
 * address, on which the internal address pointer is currently set.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @return The data from the last accessed register.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t pac1944_read_last_accessed_register ( pac1944_t *ctx );

/**
 * @brief PAC1944 general refresh command.
 * @details This function result is identical to the REFRESH command, 
 * but it is used with the I2C General Call address (0000 000).
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 *
 * @note This allows the user to issue a REFRESH command to all of the PAC19xx
 * devices in the system with a single command.
 *
 * @endcode
 */
void pac1944_general_refresh_cmd ( pac1944_t *ctx );

/**
 * @brief PAC1944 refresh command.
 * @details The readable registers for the VBUS, VSENSE, Power, accumulator 
 * outputs and accumulator count are updated by the REFRESH command and the 
 * values will be static until the next REFRESH command.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 *
 * @note The result registers may be read by the master at any time and will
 * retain the same values until the next REFRESH command is sent. This
 * function has 1 ms delay included within.
 *
 * @endcode
 */
void pac1944_refresh_cmd ( pac1944_t *ctx );

/**
 * @brief PAC1944 volatile refresh command.
 * @details If the user wants to read VSENSE and VBUS results, the most recent 
 * Power calculation, and/or the accumulator values and count without resetting 
 * the accumulators, this command may be sent.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 *
 * @note This function has 1 ms delay included within.
 *
 * @endcode
 */
void pac1944_volatile_refresh_cmd ( pac1944_t *ctx );

/**
 * @brief PAC1944 accumulator count function.
 * @details This function can be used to acquire the accumulator count value.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @return The accumulator count value.
 *
 * @note None.
 *
 * @endcode
 */
uint32_t pac1944_get_accumulator_count( pac1944_t *ctx );

/**
 * @brief PAC1944 get accumulator output function.
 * @details This function can be used to get the accumulator output value for 
 * the selected channel.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @param[in] ch_sel : Channel selection.
 *     @li @c 1 ( PAC1944_CH_SEL_CH_1 ) - Sets the channel 1 of the PAC1944,
 *     @li @c 2 ( PAC1944_CH_SEL_CH_2 ) - Sets the channel 2 of the PAC1944,
 *     @li @c 3 ( PAC1944_CH_SEL_CH_3 ) - Sets the channel 3 of the PAC1944,
 *     @li @c 4 ( PAC1944_CH_SEL_CH_4 ) - Sets the channel 4 of the PAC1944.
 * @param[out] acc_out : Pointer to accumulator output data store.
 *
 * @note None.
 *
 * @endcode
 */
void pac1944_get_accumulator_output( pac1944_t *ctx, uint8_t ch_sel, uint8_t *acc_out );

/**
 * @brief PAC1944 get measurement function.
 * @details This function can be used to get the target measurement raw data for the
 * desired channel.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @param[in] meas_sel : Measurement selection.
 *     @li @c 0 ( PAC1944_MEAS_SEL_V_SOURCE ) - Sets the voltage measurement,
 *     @li @c 1 ( PAC1944_MEAS_SEL_I_SENSE ) - Sets the current measurement,
 *     @li @c 2 ( PAC1944_MEAS_SEL_P_SENSE ) - Sets the power measurement.
 * @param[in] ch_sel : Channel selection.
 *     @li @c 1 ( PAC1944_CH_SEL_CH_1 ) - Sets the channel 1 of the PAC1944,
 *     @li @c 2 ( PAC1944_CH_SEL_CH_2 ) - Sets the channel 2 of the PAC1944,
 *     @li @c 3 ( PAC1944_CH_SEL_CH_3 ) - Sets the channel 3 of the PAC1944,
 *     @li @c 4 ( PAC1944_CH_SEL_CH_4 ) - Sets the channel 4 of the PAC1944.
 * @param[in] avg_sel : Sets the averaging mode of measurements.
 *     @li @c 0 ( PAC1944_AVG_SEL_DISABLE ) - Results are measured only once,
 *     @li @c 1 ( PAC1944_AVG_SEL_ENABLE ) - Result is acquired from 8 most recent measurements.
 * @return Raw measurement data.
 *
 * @note None.
 *
 * @endcode
 */
uint32_t pac1944_get_measurement ( pac1944_t *ctx, uint8_t meas_sel, uint8_t ch_sel, uint8_t avg_sel );

/**
 * @brief PAC1944 get calculated measurement function.
 * @details This function returns calculated measurement depending on the settings.
 * @param[in] ctx : Click context object.
 * See #pac1944_t object definition for detailed explanation.
 * @param[in] meas_sel : Measurement selection.
 *     @li @c 0 ( PAC1944_MEAS_SEL_V_SOURCE ) - Sets the voltage measurement,
 *     @li @c 1 ( PAC1944_MEAS_SEL_I_SENSE ) - Sets the current measurement,
 *     @li @c 2 ( PAC1944_MEAS_SEL_P_SENSE ) - Sets the power measurement.
 * @param[in] ch_sel : Channel selection.
 *     @li @c 1 ( PAC1944_CH_SEL_CH_1 ) - Sets the channel 1 of the PAC1944,
 *     @li @c 2 ( PAC1944_CH_SEL_CH_2 ) - Sets the channel 2 of the PAC1944,
 *     @li @c 3 ( PAC1944_CH_SEL_CH_3 ) - Sets the channel 3 of the PAC1944,
 *     @li @c 4 ( PAC1944_CH_SEL_CH_4 ) - Sets the channel 4 of the PAC1944.
 * @param[in] avg_sel : Sets the averaging mode of measurements.
 *     @li @c 0 ( PAC1944_AVG_SEL_DISABLE ) - Results are measured only once,
 *     @li @c 1 ( PAC1944_AVG_SEL_ENABLE ) - Result is averaged from 8 most recent measurements.
 * @param[in] meas_mode : Measure mode selection.
 *     @li @c 0 ( PAC1944_MEAS_MODE_UNIPOLAR_FSR ) - Unipolar measurement mode,
 *     @li @c 1 ( PAC1944_MEAS_MODE_BIPOLAR_FSR ) - Bipolar measurement mode,
 *     @li @c 2 ( PAC1944_MEAS_MODE_BIPOLAR_HALF_FSR ) - Bipolar measurement mode reduced by half.
 * @return Calculated measurement data.
 *
 * @note Measure mode has to match the configuration of the selected channel in order to
 * return the correct calculated measurement data.
 *
 * @endcode
 */
float pac1944_get_calc_measurement ( pac1944_t *ctx, uint8_t meas_sel, uint8_t ch_sel, uint8_t avg_sel, uint8_t meas_mode );

#ifdef __cplusplus
}
#endif
#endif // PAC1944_H

/*! @} */ // pac1944

// ------------------------------------------------------------------------ END
