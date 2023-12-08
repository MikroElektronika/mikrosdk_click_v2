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
 * @file ambient21.h
 * @brief This file contains API for Ambient 21 Click Driver.
 */

#ifndef AMBIENT21_H
#define AMBIENT21_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ambient21 Ambient 21 Click Driver
 * @brief API for configuring and manipulating Ambient 21 Click driver.
 * @{
 */

/**
 * @defgroup ambient21_reg Ambient 21 Registers List
 * @brief List of registers of Ambient 21 Click driver.
 */

/**
 * @addtogroup ambient21_reg
 * @{
 */

/**
 * @brief Ambient 21 registers list.
 * @details Specified registers list of Ambient 21 Click driver.
 */
#define AMBIENT21_REG_ENABLE                0x00
#define AMBIENT21_REG_CONFIG                0x01
#define AMBIENT21_REG_AILTL                 0x04
#define AMBIENT21_REG_AILTH                 0x05
#define AMBIENT21_REG_AIHTL                 0x06
#define AMBIENT21_REG_AIHTH                 0x07
#define AMBIENT21_REG_NPAILTL               0x08
#define AMBIENT21_REG_NPAILTH               0x09
#define AMBIENT21_REG_NPAIHTL               0x0A
#define AMBIENT21_REG_NPAIHTH               0x0B
#define AMBIENT21_REG_PERSIST               0x0C
#define AMBIENT21_REG_PID                   0x11
#define AMBIENT21_REG_ID                    0x12
#define AMBIENT21_REG_STATUS                0x13
#define AMBIENT21_REG_C0DATAL               0x14
#define AMBIENT21_REG_C0DATAH               0x15
#define AMBIENT21_REG_C1DATAL               0x16
#define AMBIENT21_REG_C1DATAH               0x17

/*! @} */ // ambient21_reg

/**
 * @defgroup ambient21_set Ambient 21 Registers Settings
 * @brief Settings for registers of Ambient 21 Click driver.
 */

/**
 * @addtogroup ambient21_set
 * @{
 */

/**
 * @brief Ambient 21 command register setting.
 * @details Specified setting for Command register of Ambient 21 Click driver.
 */
#define AMBIENT21_CMD_NORMAL_OP             0xA0
#define AMBIENT21_CMD_SPEC_FUNC             0xE0
#define AMBIENT21_SF_INT_SET                0x04
#define AMBIENT21_SF_CLEAR_ALS_INT          0x06
#define AMBIENT21_SF_CLEAR_ALS_NOPERS_INT   0x07
#define AMBIENT21_SF_CLEAR_NOPERS_INT       0x0A
#define AMBIENT21_ADDR_SF_MASK              0x1F

/**
 * @brief Ambient 21 enable register setting.
 * @details Specified setting for enable register of Ambient 21 Click driver.
 */
#define AMBIENT21_ENABLE_NPIEN              0x80
#define AMBIENT21_ENABLE_SAI                0x40
#define AMBIENT21_ENABLE_AIEN               0x10
#define AMBIENT21_ENABLE_AEN                0x02
#define AMBIENT21_ENABLE_PON                0x01

/**
 * @brief Ambient 21 config register setting.
 * @details Specified setting for config register of Ambient 21 Click driver.
 */
#define AMBIENT21_CONFIG_SRESET             0x80
#define AMBIENT21_CONFIG_AGAIN_LOW          0x00
#define AMBIENT21_CONFIG_AGAIN_MID          0x10
#define AMBIENT21_CONFIG_AGAIN_HIGH         0x20
#define AMBIENT21_CONFIG_AGAIN_MAX          0x30
#define AMBIENT21_CONFIG_AGAIN_MASK         0x30
#define AMBIENT21_CONFIG_ATIME_100MS        0x00
#define AMBIENT21_CONFIG_ATIME_200MS        0x01
#define AMBIENT21_CONFIG_ATIME_300MS        0x02
#define AMBIENT21_CONFIG_ATIME_400MS        0x03
#define AMBIENT21_CONFIG_ATIME_500MS        0x04
#define AMBIENT21_CONFIG_ATIME_600MS        0x05
#define AMBIENT21_CONFIG_ATIME_MASK         0x07

/**
 * @brief Ambient 21 persist register setting.
 * @details Specified setting for persist register of Ambient 21 Click driver.
 */
#define AMBIENT21_PERSIST_EVERY             0x00
#define AMBIENT21_PERSIST_ANY               0x01
#define AMBIENT21_PERSIST_2                 0x02
#define AMBIENT21_PERSIST_3                 0x03
#define AMBIENT21_PERSIST_5                 0x04
#define AMBIENT21_PERSIST_10                0x05
#define AMBIENT21_PERSIST_15                0x06
#define AMBIENT21_PERSIST_20                0x07
#define AMBIENT21_PERSIST_25                0x08
#define AMBIENT21_PERSIST_30                0x09
#define AMBIENT21_PERSIST_35                0x0A
#define AMBIENT21_PERSIST_40                0x0B
#define AMBIENT21_PERSIST_45                0x0C
#define AMBIENT21_PERSIST_50                0x0D
#define AMBIENT21_PERSIST_55                0x0E
#define AMBIENT21_PERSIST_60                0x0F
#define AMBIENT21_PERSIST_MASK              0x0F

/**
 * @brief Ambient 21 status register setting.
 * @details Specified setting for status register of Ambient 21 Click driver.
 */
#define AMBIENT21_STATUS_NPINTR             0x20
#define AMBIENT21_STATUS_AINT               0x10
#define AMBIENT21_STATUS_AVALID             0x01

/**
 * @brief Ambient 21 ID values.
 * @details Specified ID values of Ambient 21 Click driver.
 */
#define AMBIENT21_DEVICE_ID                 0x50

/**
 * @brief Ambient 21 again and atime setting.
 * @details Specified setting for again and atime of Ambient 21 Click driver.
 */
#define AMBIENT21_AGAIN_LOW                 0x00
#define AMBIENT21_AGAIN_MID                 0x01
#define AMBIENT21_AGAIN_HIGH                0x02
#define AMBIENT21_AGAIN_MAX                 0x03
#define AMBIENT21_ATIME_100MS               0x00
#define AMBIENT21_ATIME_200MS               0x01
#define AMBIENT21_ATIME_300MS               0x02
#define AMBIENT21_ATIME_400MS               0x03
#define AMBIENT21_ATIME_500MS               0x04
#define AMBIENT21_ATIME_600MS               0x05

/**
 * @brief Ambient 21 lux calculation values.
 * @details Specified lux calculation values of Ambient 21 Click driver.
 */
#define AMBIENT21_GAIN_0                    1.0f
#define AMBIENT21_GAIN_1                    25.0f
#define AMBIENT21_GAIN_2                    428.0f
#define AMBIENT21_GAIN_3                    9876.0f
#define AMBIENT21_TIME_RES                  100.0f
#define AMBIENT21_LUX_GDF                   900.0f
#define AMBIENT21_LUX_COEF                  1.0f

/**
 * @brief Ambient 21 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 21 Click driver.
 */
#define AMBIENT21_DEVICE_ADDRESS            0x29

/*! @} */ // ambient21_set

/**
 * @defgroup ambient21_map Ambient 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 21 Click driver.
 */

/**
 * @addtogroup ambient21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 21 Click to the selected MikroBUS.
 */
#define AMBIENT21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient21_map
/*! @} */ // ambient21

/**
 * @brief Ambient 21 Click context object.
 * @details Context object definition of Ambient 21 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin (Active low). */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    
    float   atime_ms;               /**< ALS time in milliseconds. */
    float   again;                  /**< ALS gain level. */
    float   cpl;                    /**< Counts per LUX value calculated when ATIME or AGAIN is changed. */

} ambient21_t;

/**
 * @brief Ambient 21 Click configuration object.
 * @details Configuration object definition of Ambient 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;             /**< Interrupt pin (Active low). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} ambient21_cfg_t;

/**
 * @brief Ambient 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT21_OK = 0,
    AMBIENT21_ERROR = -1

} ambient21_return_value_t;

/*!
 * @addtogroup ambient21 Ambient 21 Click Driver
 * @brief API for configuring and manipulating Ambient 21 Click driver.
 * @{
 */

/**
 * @brief Ambient 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient21_cfg_setup ( ambient21_cfg_t *cfg );

/**
 * @brief Ambient 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_init ( ambient21_t *ctx, ambient21_cfg_t *cfg );

/**
 * @brief Ambient 21 default configuration function.
 * @details This function executes a default configuration of Ambient 21
 * click board.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient21_default_cfg ( ambient21_t *ctx );

/**
 * @brief Ambient 21 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 13 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_generic_write ( ambient21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Ambient 21 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read (up to 24 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_generic_read ( ambient21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Ambient 21 write register function.
 * @details This function writes data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_write_register ( ambient21_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Ambient 21 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_read_register ( ambient21_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Ambient 21 write spec func function.
 * @details This function writes a special function command byte.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[in] spec_func : Special function command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_write_spec_func ( ambient21_t *ctx, uint8_t spec_func );

/**
 * @brief Ambient 21 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ambient21_get_int_pin ( ambient21_t *ctx );

/**
 * @brief Ambient 21 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_check_communication ( ambient21_t *ctx );

/**
 * @brief Ambient 21 clear interrupts function.
 * @details This function clears all interrupts by sending the INT clear special function command.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_clear_interrupts ( ambient21_t *ctx );

/**
 * @brief Ambient 21 set config function.
 * @details This function sets again and atime settings and calculates the @b ctx->cpl.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[in] again : ALS gain level
 *                    @li @c 0 - 1X,
 *                    @li @c 1 - 25X,
 *                    @li @c 2 - 428X,
 *                    @li @c 3 - 9876X.
 * @param[in] atime : ALS time
 *                    @li @c 0 - 100ms,
 *                    @li @c 1 - 200ms,
 *                    @li @c 2 - 300ms,
 *                    @li @c 3 - 400ms,
 *                    @li @c 4 - 500ms,
 *                    @li @c 5 - 600ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_set_config ( ambient21_t *ctx, uint8_t again, uint8_t atime );

/**
 * @brief Ambient 21 read raw data function.
 * @details This function checks if the data is ready and then reads the raw ADC data from two channels.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[out] ch_0 : Raw data from channel 0.
 * @param[out] ch_1 : Raw data from channel 1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient21_read_raw_data ( ambient21_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );

/**
 * @brief Ambient 21 measure light level function.
 * @details This function reads the raw ADC data from two channels and then measures the light
 * level in lux based on those readings.
 * @param[in] ctx : Click context object.
 * See #ambient21_t object definition for detailed explanation.
 * @param[out] lux : Ambient light level in Lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note In order to improve the lux calculation accuracy, measure and adjust
 * the @b AMBIENT21_LUX_GDF (glass and device factors) value.
 */
err_t ambient21_measure_light_level ( ambient21_t *ctx, uint16_t *lux );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT21_H

/*! @} */ // ambient21

// ------------------------------------------------------------------------ END
