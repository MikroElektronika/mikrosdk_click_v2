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
 * @file pac1954.h
 * @brief This file contains API for PAC1954 Click Driver.
 */

#ifndef PAC1954_H
#define PAC1954_H

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
 * @addtogroup pac1954 PAC1954 Click Driver
 * @brief API for configuring and manipulating PAC1954 Click driver.
 * @{
 */

/**
 * @defgroup pac1954_reg PAC1954 Registers List
 * @brief List of registers of PAC1954 Click driver.
 */

/**
 * @addtogroup pac1954_reg
 * @{
 */

/**
 * @brief PAC1954 Registers List.
 * @details List of registers of PAC1954 Click driver.
 */
#define PAC1954_REG_REFRESH                   0x00
#define PAC1954_REG_CTRL                      0x01
#define PAC1954_REG_ACC_COUNT                 0x02
#define PAC1954_REG_VACC_CH1                  0x03
#define PAC1954_REG_VACC_CH2                  0x04
#define PAC1954_REG_VACC_CH3                  0x05
#define PAC1954_REG_VACC_CH4                  0x06
#define PAC1954_REG_VBUS_CH1                  0x07
#define PAC1954_REG_VBUS_CH2                  0x08
#define PAC1954_REG_VBUS_CH3                  0x09
#define PAC1954_REG_VBUS_CH4                  0x0A
#define PAC1954_REG_VSENSE_CH1                0x0B
#define PAC1954_REG_VSENSE_CH2                0x0C
#define PAC1954_REG_VSENSE_CH3                0x0D
#define PAC1954_REG_VSENSE_CH4                0x0E
#define PAC1954_REG_VBUS_CH1_AVG              0x0F
#define PAC1954_REG_VBUS_CH2_AVG              0x10
#define PAC1954_REG_VBUS_CH3_AVG              0x11
#define PAC1954_REG_VBUS_CH4_AVG              0x12
#define PAC1954_REG_VSENSE_CH1_AVG            0x13
#define PAC1954_REG_VSENSE_CH2_AVG            0x14
#define PAC1954_REG_VSENSE_CH3_AVG            0x15
#define PAC1954_REG_VSENSE_CH4_AVG            0x16
#define PAC1954_REG_VPOWER_CH1                0x17
#define PAC1954_REG_VPOWER_CH2                0x18
#define PAC1954_REG_VPOWER_CH3                0x19
#define PAC1954_REG_VPOWER_CH4                0x1A
#define PAC1954_REG_SMBUS_CFG                 0x1C
#define PAC1954_REG_NEG_PWR_FSR               0x1D
#define PAC1954_REG_REFRESH_G                 0x1E
#define PAC1954_REG_REFRESH_V                 0x1F
#define PAC1954_REG_SLOW                      0x20
#define PAC1954_REG_CTRL_ACT                  0x21
#define PAC1954_REG_NEG_PWR_FSR_ACT           0x22
#define PAC1954_REG_CTRL_LAT                  0x23
#define PAC1954_REG_NEG_PWR_FSR_LAT           0x24
#define PAC1954_REG_ACC_CFG                   0x25
#define PAC1954_REG_ALERT_STATUS              0x26
#define PAC1954_REG_SLOW_ALERT1               0x27
#define PAC1954_REG_GPIO_ALERT2               0x28
#define PAC1954_REG_ACC_FULLNESS_LIM          0x29
#define PAC1954_REG_OC_LIM_CH1                0x30
#define PAC1954_REG_OC_LIM_CH2                0x31
#define PAC1954_REG_OC_LIM_CH3                0x32
#define PAC1954_REG_OC_LIM_CH4                0x33
#define PAC1954_REG_UC_LIM_CH1                0x34
#define PAC1954_REG_UC_LIM_CH2                0x35
#define PAC1954_REG_UC_LIM_CH3                0x36
#define PAC1954_REG_UC_LIM_CH4                0x37
#define PAC1954_REG_OP_LIM_CH1                0x38
#define PAC1954_REG_OP_LIM_CH2                0x39
#define PAC1954_REG_OP_LIM_CH3                0x3A
#define PAC1954_REG_OP_LIM_CH4                0x3B
#define PAC1954_REG_OV_LIM_CH1                0x3C
#define PAC1954_REG_OV_LIM_CH2                0x3D
#define PAC1954_REG_OV_LIM_CH3                0x3E
#define PAC1954_REG_OV_LIM_CH4                0x3F
#define PAC1954_REG_UV_LIM_CH1                0x40
#define PAC1954_REG_UV_LIM_CH2                0x41
#define PAC1954_REG_UV_LIM_CH3                0x42
#define PAC1954_REG_UV_LIM_CH4                0x43
#define PAC1954_REG_OC_LIM_NSAMPLES           0x44
#define PAC1954_REG_UC_LIM_NSAMPLES           0x45
#define PAC1954_REG_OP_LIM_NSAMPLES           0x46
#define PAC1954_REG_OV_LIM_NSAMPLES           0x47
#define PAC1954_REG_UV_LIM_NSAMPLES           0x48
#define PAC1954_REG_ALERT_ENABLE              0x49
#define PAC1954_REG_ACC_CFG_ACT               0x4A
#define PAC1954_REG_ACC_CFG_LAT               0x4B
#define PAC1954_REG_ID_PRODUCT                0xFD
#define PAC1954_REG_ID_MANUFACTURER           0xFE
#define PAC1954_REG_ID_REVISION               0xFF

/*! @} */ // pac1954_reg

/**
 * @defgroup pac1954_set PAC1954 Registers Settings
 * @brief Settings for registers of PAC1954 Click driver.
 */

/**
 * @addtogroup pac1954_set
 * @{
 */

/**
 * @brief PAC1954 Control Settings.
 * @details Specified setting for the CTRL register of PAC1954 Click driver.
 */
#define PAC1954_CTRLH_SPS_1024_ADAPT_ACC      0x00
#define PAC1954_CTRLH_SPS_256_ADAPT_ACC       0x10
#define PAC1954_CTRLH_SPS_64_ADAPT_ACC        0x20
#define PAC1954_CTRLH_SPS_8_ADAPT_ACC         0x30
#define PAC1954_CTRLH_SPS_1024                0x40
#define PAC1954_CTRLH_SPS_256                 0x50
#define PAC1954_CTRLH_SPS_64                  0x60
#define PAC1954_CTRLH_SPS_8                   0x70
#define PAC1954_CTRLH_SINGLE_SHOT_MODE        0x80
#define PAC1954_CTRLH_SINGLE_SHOT_8X          0x90
#define PAC1954_CTRLH_FAST_MODE               0xA0
#define PAC1954_CTRLH_BURST_MODE              0xB0
#define PAC1954_CTRLH_SLEEP                   0xF0
#define PAC1954_CTRLH_INT_PIN_ALERT           0x00
#define PAC1954_CTRLH_INT_PIN_DIG_IN          0x04
#define PAC1954_CTRLH_INT_PIN_DIG_OUT         0x08
#define PAC1954_CTRLH_INT_PIN_SLOW            0x0C
#define PAC1954_CTRLH_SLW_PIN_ALERT           0x00
#define PAC1954_CTRLH_SLW_PIN_DIG_IN          0x01
#define PAC1954_CTRLH_SLW_PIN_DIG_OUT         0x02
#define PAC1954_CTRLH_SLW_PIN_SLOW            0x03
#define PAC1954_CTRLL_CH1_OFF                 0x80
#define PAC1954_CTRLL_CH2_OFF                 0x40
#define PAC1954_CTRLL_CH3_OFF                 0x20
#define PAC1954_CTRLL_CH4_OFF                 0x10
#define PAC1954_CTRLL_ALL_CH_OFF              0xF0
#define PAC1954_CTRLL_ALL_CH_ON               0x00

/**
 * @brief PAC1954 Measurement Type Offset For Channels.
 * @details Specified setting for NEG_PWR_FSR register of PAC1954 Click driver.
 */
#define PAC1954_NEG_PWR_FSR_CH1_OFFSET        6
#define PAC1954_NEG_PWR_FSR_CH2_OFFSET        4
#define PAC1954_NEG_PWR_FSR_CH3_OFFSET        2
#define PAC1954_NEG_PWR_FSR_CH4_OFFSET        0

/**
 * @brief PAC1954 SMBus Settings.
 * @details Specified setting for SMBUS SETTINGS register of PAC1954 Click driver.
 */
#define PAC1954_SMBUS_INT_PIN_MASK            0x80
#define PAC1954_SMBUS_SLW_PIN_MASK            0x40
#define PAC1954_SMBUS_ALERT_MASK              0x20
#define PAC1954_SMBUS_POR_MASK                0x10
#define PAC1954_SMBUS_TIMEOUT_OFF             0x00
#define PAC1954_SMBUS_TIMEOUT_ON              0x08
#define PAC1954_SMBUS_BYTE_COUNT_OFF          0x00
#define PAC1954_SMBUS_BYTE_COUNT_ON           0x04
#define PAC1954_SMBUS_AUTO_INC_SKIP_ON        0x00
#define PAC1954_SMBUS_AUTO_INC_SKIP_OFF       0x02
#define PAC1954_SMBUS_I2C_HIGH_SPEED          0x01

/**
 * @brief PAC1954 Measurement Data Selector.
 * @details Measurement data selection of PAC1954 Click driver.
 */
#define PAC1954_MEAS_SEL_V_SOURCE             0
#define PAC1954_MEAS_SEL_I_SENSE              1
#define PAC1954_MEAS_SEL_P_SENSE              2

/**
 * @brief PAC1954 Channel Selector.
 * @details Channel selection of PAC1954 Click driver.
 */
#define PAC1954_CH_SEL_CH_1                   1
#define PAC1954_CH_SEL_CH_2                   2
#define PAC1954_CH_SEL_CH_3                   3
#define PAC1954_CH_SEL_CH_4                   4

/**
 * @brief PAC1954 Average Selector.
 * @details Selection for averaged or single data used in calculations of PAC1954 Click driver.
 */
#define PAC1954_AVG_SEL_DISABLE               0
#define PAC1954_AVG_SEL_ENABLE                1

/**
 * @brief PAC1954 Measurement Type Definition.
 * @details Type of measurement data of PAC1954 Click driver.
 */
#define PAC1954_MEAS_MODE_UNIPOLAR_FSR        0
#define PAC1954_MEAS_MODE_BIPOLAR_FSR         1
#define PAC1954_MEAS_MODE_BIPOLAR_HALF_FSR    2

/**
 * @brief PAC1954 SLW Pin Settings.
 * @details Settings for the Slow pin of PAC1954 Click driver.
 */
#define PAC1954_ALL_CH_SAMPLE_8SPS_ON         1
#define PAC1954_ALL_CH_SAMPLE_8SPS_OFF        0

/**
 * @brief PAC1954 Device Power Control.
 * @details Power control using EN pin of PAC1954 Click driver.
 */
#define PAC1954_DEV_ENABLE                    1
#define PAC1954_DEV_PWR_DWN                   0

/**
 * @brief PAC1954 Alert Indicator.
 * @details Alert indicator of PAC1954 Click driver.
 */
#define PAC1954_ALERT_ACTIVE                  0
#define PAC1954_ALERT_INACTIVE                1

/**
 * @brief PAC1954 device address setting.
 * @details Specified setting for device slave address selection of
 * PAC1954 Click driver.
 */
#define PAC1954_DEV_ADDR_0                    0x10
#define PAC1954_DEV_ADDR_1                    0x1F

/*! @} */ // pac1954_set

/**
 * @defgroup pac1954_map PAC1954 MikroBUS Map
 * @brief MikroBUS pin mapping of PAC1954 Click driver.
 */

/**
 * @addtogroup pac1954_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PAC1954 Click to the selected MikroBUS.
 */
#define PAC1954_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.slw = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pac1954_map
/*! @} */ // pac1954

/**
 * @brief PAC1954 Click context object.
 * @details Context object definition of PAC1954 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;       /**< Chip Enable. */
    digital_out_t  slw;      /**< Conversion Rate Control. */

    // Input pins
    digital_in_t  int_pin;   /**< Interrupt. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} pac1954_t;

/**
 * @brief PAC1954 Click configuration object.
 * @details Configuration object definition of PAC1954 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;         /**< Chip Enable. */
    pin_name_t  slw;        /**< Conversion Rate Control. */
    pin_name_t  int_pin;    /**< Interrupt. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} pac1954_cfg_t;

/**
 * @brief PAC1954 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PAC1954_OK = 0,
    PAC1954_ERROR = -1

} pac1954_return_value_t;

/*!
 * @addtogroup pac1954 PAC1954 Click Driver
 * @brief API for configuring and manipulating PAC1954 Click driver.
 * @{
 */

/**
 * @brief PAC1954 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pac1954_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pac1954_cfg_setup ( pac1954_cfg_t *cfg );

/**
 * @brief PAC1954 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pac1954_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_init ( pac1954_t *ctx, pac1954_cfg_t *cfg );

/**
 * @brief PAC1954 default configuration function.
 * @details This function executes a default configuration of PAC1954
 * click board.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pac1954_default_cfg ( pac1954_t *ctx );

/**
 * @brief PAC1954 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_generic_write ( pac1954_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief PAC1954 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_generic_read ( pac1954_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief PAC1954 Single Byte Write Function.
 * @details This function writes single data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_single_write ( pac1954_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PAC1954 Single Byte Read Function.
 * @details This function reads single data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_single_read ( pac1954_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PAC1954 Set Address Pointer Function.
 * @details This function allows user to set the internal address pointer on
 * the desired register.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_set_address_pointer ( pac1954_t *ctx, uint8_t reg );

/**
 * @brief PAC1954 Last Accessed Register Read Function.
 * @details This function allows user to read the last accessed register
 * address, on which the internal address pointer is currently set.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_read_last_access_reg ( pac1954_t *ctx, uint8_t *data_out );

/**
 * @brief PAC1954 Refresh Command.
 * @details This function updates the readable registers for the VBUS, VSENSE, Power, accumulator 
 * outputs and accumulator count by issuing the REFRESH command. The values will be static until 
 * the next REFRESH command.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note These readable registers will be stable within 1 ms from sending the 
 * REFRESH command, and may be read by the master at any time up until the next 
 * REFRESH command is sent.
 */
err_t pac1954_refresh_cmd ( pac1954_t *ctx );

/**
 * @brief PAC1954 Volatile Refresh Command.
 * @details If the user wants to read VSENSE and VBUS results, the most recent 
 * Power calculation, and/or the accumulator values and count without resetting 
 * the accumulators, this command may be sent. 
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Sending this command and waiting 1 ms ensures that the VSENSE, VBUS, 
 * Power, accumulator, and accumulator count values will be stable.
 */
err_t pac1954_vol_refresh_cmd ( pac1954_t *ctx );

/**
 * @brief PAC1954 Get Measurement Function.
 * @details This function can be used to get the target measurement data for the
 * desired channel.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] meas_sel : Measurement data selector.
 * @param[in] ch_sel : Channel selector.
 * @param[in] avg_sel : Selector for using averaged or one sample data.
 * This parameter will be ignored for reading Power measurement.
 * @param[out] data_out : The target measurement data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_get_measurement ( pac1954_t *ctx, uint8_t meas_sel, uint8_t ch_sel, 
                                uint8_t avg_sel, uint32_t *data_out );

/**
 * @brief PAC1954 Get Accumulator Count Function.
 * @details This function can be used to get the accumulator count value.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[out] data_out : The accumulator count value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_get_acc_count ( pac1954_t *ctx, uint32_t *data_out );

/**
 * @brief PAC1954 Get Accumulator Output Function.
 * @details This function can be used to get the accumulator output value for 
 * the selected channel.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] ch_sel : Channel selector.
 * @param[out] data_out : The accumulator output values [7 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_get_acc_output ( pac1954_t *ctx, uint8_t ch_sel, uint8_t *data_out );

/**
 * @brief PAC1954 Get Calculated Measurement Function.
 * @details This function calls the function for getting the selected 
 * measurement data and performs all the necessary calculations to get 
 * the measurement value in standard unit.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] meas_sel : Measurement data selector.
 * @param[in] ch_sel : Channel selector.
 * @param[in] avg_sel : Selector for using averaged or one sample data.
 * This parameter will be ignored for reading Power measurement.
 * @param[in] meas_mode : Measurement type of data selector.
 * @param[out] data_out : The calculated measurement data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1954_get_calc_measurement ( pac1954_t *ctx, uint8_t meas_sel, uint8_t ch_sel, 
                                     uint8_t avg_sel, uint8_t meas_mode, float *data_out );

/**
 * @brief PAC1954 Slow Down Sampling Freq Of All Channels Function.
 * @details This function sets sampling frequency at 8 SPS for all channels 
 * using SLW pin.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] state : SLW pin logic state.
 * @return None.
 * @note None.
 */
void pac1954_set_ch_8_sps ( pac1954_t *ctx, uint8_t state );

/**
 * @brief PAC1954 Power Control Function.
 * @details This function executes a power control of the PAC1954 click using 
 * EN pin.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @param[in] state : EN pin logic state.
 * @return None.
 * @note None.
 */
void pac1954_enable ( pac1954_t *ctx, uint8_t state );

/**
 * @brief PAC1954 Get INT Pin State Function.
 * @details This function checks the state of the INT pin which has role as 
 * Alert2 pin by default.
 * @param[in] ctx : Click context object.
 * See #pac1954_t object definition for detailed explanation.
 * @return INT pin logic state..
 * @note None.
 */
uint8_t pac1954_get_alert2_status ( pac1954_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PAC1954_H

/*! @} */ // pac1954

// ------------------------------------------------------------------------ END
