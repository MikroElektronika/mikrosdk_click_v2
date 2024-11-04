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
 * @file pac1720.h
 * @brief This file contains API for PAC1720 Click Driver.
 */

#ifndef PAC1720_H
#define PAC1720_H

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
 * @addtogroup pac1720 PAC1720 Click Driver
 * @brief API for configuring and manipulating PAC1720 Click driver.
 * @{
 */

/**
 * @defgroup pac1720_reg PAC1720 Registers List
 * @brief List of registers of PAC1720 Click driver.
 */

/**
 * @addtogroup pac1720_reg
 * @{
 */

/**
 * @brief PAC1720 register list.
 * @details Specified register list of PAC1720 Click driver.
 */
#define PAC1720_REG_CONFIG                      0x00
#define PAC1720_REG_CONVERSION_RATE             0x01
#define PAC1720_REG_ONE_SHOT                    0x02
#define PAC1720_REG_CHANNEL_MASK                0x03
#define PAC1720_REG_HIGH_LIMIT_STATUS           0x04
#define PAC1720_REG_LOW_LIMIT_STATUS            0x05
#define PAC1720_REG_VSOURCE_CONFIG              0x0A
#define PAC1720_REG_CH1_VSENSE_CONFIG           0x0B
#define PAC1720_REG_CH2_VSENSE_CONFIG           0x0C
#define PAC1720_REG_CH1_VSENSE_HIGH_BYTE        0x0D
#define PAC1720_REG_CH1_VSENSE_LOW_BYTE         0x0E
#define PAC1720_REG_CH2_VSENSE_HIGH_BYTE        0x0F
#define PAC1720_REG_CH2_VSENSE_LOW_BYTE         0x10
#define PAC1720_REG_CH1_VSOURCE_HIGH_BYTE       0x11
#define PAC1720_REG_CH1_VSOURCE_LOW_BYTE        0x12
#define PAC1720_REG_CH2_VSOURCE_HIGH_BYTE       0x13
#define PAC1720_REG_CH2_VSOURCE_LOW_BYTE        0x14
#define PAC1720_REG_CH1_POWER_RATIO_HIGH_BYTE   0x15
#define PAC1720_REG_CH1_POWER_RATIO_LOW_BYTE    0x16
#define PAC1720_REG_CH2_POWER_RATIO_HIGH_BYTE   0x17
#define PAC1720_REG_CH2_POWER_RATIO_LOW_BYTE    0x18
#define PAC1720_REG_CH1_VSENSE_HIGH_LIMIT       0x19
#define PAC1720_REG_CH2_VSENSE_HIGH_LIMIT       0x1A
#define PAC1720_REG_CH1_VSENSE_LOW_LIMIT        0x1B
#define PAC1720_REG_CH2_VSENSE_LOW_LIMIT        0x1C
#define PAC1720_REG_CH1_VSOURCE_HIGH_LIMIT      0x1D
#define PAC1720_REG_CH2_VSOURCE_HIGH_LIMIT      0x1E
#define PAC1720_REG_CH1_VSOURCE_LOW_LIMIT       0x1F
#define PAC1720_REG_CH2_VSOURCE_LOW_LIMIT       0x20
#define PAC1720_REG_PRODUCT_ID                  0xFD
#define PAC1720_REG_MANUFACTURER_ID             0xFE
#define PAC1720_REG_REVISION                    0xFF

/*! @} */ // pac1720_reg

/**
 * @defgroup pac1720_set PAC1720 Registers Settings
 * @brief Settings for registers of PAC1720 Click driver.
 */

/**
 * @addtogroup pac1720_set
 * @{
 */

/**
 * @brief PAC1720 measurement calculation values.
 * @details Specified measurement calculation values of PAC1720 Click driver.
 */
#define PAC1720_MAX_VOLTAGE                     40.0
#define PAC1720_CURRENT_SENSE_RANGE_V           0.010
#define PAC1720_RSENSE_OHM                      0.004
#define PAC1720_POWER_RATIO_RESOLUTION          65535

/**
 * @brief PAC1720 product ID value.
 * @details Specified product ID value of PAC1720 Click driver.
 */
#define PAC1720_PRODUCT_ID                      0x57

/**
 * @brief PAC1720 device address setting.
 * @details Specified setting for device slave address selection of
 * PAC1720 Click driver.
 */
#define PAC1720_SET_DEV_ADDR_SEL_0_OHM          0x4C
#define PAC1720_SET_DEV_ADDR_SEL_100_OHM        0x4D
#define PAC1720_SET_DEV_ADDR_SEL_180_OHM        0x4E
#define PAC1720_SET_DEV_ADDR_SEL_300_OHM        0x4F
#define PAC1720_SET_DEV_ADDR_SEL_430_OHM        0x48
#define PAC1720_SET_DEV_ADDR_SEL_560_OHM        0x49
#define PAC1720_SET_DEV_ADDR_SEL_750_OHM        0x4A
#define PAC1720_SET_DEV_ADDR_SEL_1270_OHM       0x4B
#define PAC1720_SET_DEV_ADDR_SEL_1600_OHM       0x28
#define PAC1720_SET_DEV_ADDR_SEL_2000_OHM       0x29
#define PAC1720_SET_DEV_ADDR_SEL_2700_OHM       0x2A
#define PAC1720_SET_DEV_ADDR_SEL_3600_OHM       0x2B
#define PAC1720_SET_DEV_ADDR_SEL_5600_OHM       0x2C
#define PAC1720_SET_DEV_ADDR_SEL_9100_OHM       0x2D
#define PAC1720_SET_DEV_ADDR_SEL_20000_OHM      0x2E
#define PAC1720_SET_DEV_ADDR_SEL_OPEN           0x18

/*! @} */ // pac1720_set

/**
 * @defgroup pac1720_map PAC1720 MikroBUS Map
 * @brief MikroBUS pin mapping of PAC1720 Click driver.
 */

/**
 * @addtogroup pac1720_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PAC1720 Click to the selected MikroBUS.
 */
#define PAC1720_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pac1720_map
/*! @} */ // pac1720

/**
 * @brief PAC1720 Click context object.
 * @details Context object definition of PAC1720 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;          /**< Alarm pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    
    uint8_t ch1_vsrc_cfg;
    uint8_t ch1_vsense_cfg;
    
    uint8_t ch2_vsrc_cfg;
    uint8_t ch2_vsense_cfg;

} pac1720_t;

/**
 * @brief PAC1720 Click configuration object.
 * @details Configuration object definition of PAC1720 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;            /**< Alarm pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} pac1720_cfg_t;

/**
 * @brief PAC1720 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PAC1720_OK = 0,
    PAC1720_ERROR = -1

} pac1720_return_value_t;

/**
 * @brief PAC1720 channel selection.
 * @details Predefined enum values for channel selection.
 */
typedef enum
{
    PAC1720_CHANNEL_1 = 1,
    PAC1720_CHANNEL_2 = 2

} pac1720_ch_sel_t;

/**
 * @brief PAC1720 sample time setting.
 * @details Predefined enum values for sample time setting.
 * @note The values above 20ms are not supported for Vsource settings.
 */
typedef enum
{
    PAC1720_SAMPLE_TIME_2p5mS = 0,
    PAC1720_SAMPLE_TIME_5mS,
    PAC1720_SAMPLE_TIME_10mS,
    PAC1720_SAMPLE_TIME_20mS,
    PAC1720_SAMPLE_TIME_40mS,
    PAC1720_SAMPLE_TIME_80mS,
    PAC1720_SAMPLE_TIME_160mS,
    PAC1720_SAMPLE_TIME_320mS

} pac1720_sample_time_t;

/**
 * @brief PAC1720 averaging setting.
 * @details Predefined enum values for averaging samples setting.
 */
typedef enum
{
    PAC1720_AVG_DISABLE = 0,
    PAC1720_AVG_2_SAMPLES,
    PAC1720_AVG_4_SAMPLES,
    PAC1720_AVG_8_SAMPLES

} pac1720_avg_t;

/**
 * @brief PAC1720 current sensing range setting.
 * @details Predefined enum values for current sensing range setting.
 */
typedef enum
{
    PAC1720_CS_RANGE_10mV = 0,
    PAC1720_CS_RANGE_20mV,
    PAC1720_CS_RANGE_40mV,
    PAC1720_CS_RANGE_80mV

} pac1720_cs_rng_t;

/*!
 * @addtogroup pac1720 PAC1720 Click Driver
 * @brief API for configuring and manipulating PAC1720 Click driver.
 * @{
 */

/**
 * @brief PAC1720 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pac1720_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pac1720_cfg_setup ( pac1720_cfg_t *cfg );

/**
 * @brief PAC1720 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pac1720_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_init ( pac1720_t *ctx, pac1720_cfg_t *cfg );

/**
 * @brief PAC1720 default configuration function.
 * @details This function executes a default configuration of PAC1720
 * Click board.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pac1720_default_cfg ( pac1720_t *ctx );

/**
 * @brief PAC1720 write block function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_write_block ( pac1720_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief PAC1720 read block function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_read_block ( pac1720_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief PAC1720 write byte function.
 * @details This function writes single data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_write_byte ( pac1720_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PAC1720 read byte function.
 * @details This function reads single data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_read_byte ( pac1720_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PAC1720 set address pointer function.
 * @details This function allows user to set the internal address pointer on
 * the desired register.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_set_address_pointer ( pac1720_t *ctx, uint8_t reg );

/**
 * @brief PAC1720 read last accessed register function.
 * @details This function allows user to read the last accessed register
 * address, on which the internal address pointer is currently set.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_read_last_accessed_register ( pac1720_t *ctx, uint8_t *data_out );

/**
 * @brief PAC1720 set slave address function.
 * @details This function sets the slave address for I2C communication.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] slave_address : Slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_set_slave_address ( pac1720_t *ctx, uint8_t slave_address );

/**
 * @brief PAC1720 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pac1720_get_int_pin ( pac1720_t *ctx );

/**
 * @brief PAC1720 check communication function.
 * @details This function checks the communication by reading and verifying the product ID.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_check_communication ( pac1720_t *ctx );

/**
 * @brief PAC1720 set vsource config function.
 * @details This function sets the Voltage Source configuration (sample time and average samples) 
 * for the selected channel.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] ch : Channel selection.
 * See #pac1720_ch_sel_t enum definition for detailed explanation.
 * @param[in] stime : Sample time selection.
 * See #pac1720_sample_time_t enum definition for detailed explanation.
 * @param[in] avg : Average samples selection.
 * See #pac1720_avg_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_set_vsource_config ( pac1720_t *ctx, pac1720_ch_sel_t ch, 
                                   pac1720_sample_time_t stime, pac1720_avg_t avg );

/**
 * @brief PAC1720 set vsense config function.
 * @details This function sets the Voltage Sense configuration (sample time, average samples, 
 * and sampling range) for the selected channel.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] ch : Channel selection.
 * See #pac1720_ch_sel_t enum definition for detailed explanation.
 * @param[in] stime : Sample time selection.
 * See #pac1720_sample_time_t enum definition for detailed explanation.
 * @param[in] avg : Average samples selection.
 * See #pac1720_avg_t enum definition for detailed explanation.
 * @param[in] cs_rng : Current sampling range selection.
 * See #pac1720_cs_rng_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1720_set_vsense_config ( pac1720_t *ctx, pac1720_ch_sel_t ch, pac1720_sample_time_t stime, 
                                  pac1720_avg_t avg, pac1720_cs_rng_t cs_rng );

/**
 * @brief PAC1720 get measurements function.
 * @details This function reads voltage, current, and power from the selected channel.
 * @param[in] ctx : Click context object.
 * See #pac1720_t object definition for detailed explanation.
 * @param[in] ch : Channel selection.
 * See #pac1720_ch_sel_t enum definition for detailed explanation.
 * @param[out] voltage : Voltage [V].
 * @param[out] current : Current [A].
 * @param[out] power : Power [W].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Vsource and Vsense must be configured with pac1720_set_vsource_config and 
 * pac1720_set_vsense_config functions before calling this function.
 */
err_t pac1720_get_measurements ( pac1720_t *ctx, pac1720_ch_sel_t ch, 
                                 float *voltage, float *current, float *power );

#ifdef __cplusplus
}
#endif
#endif // PAC1720_H

/*! @} */ // pac1720

// ------------------------------------------------------------------------ END
