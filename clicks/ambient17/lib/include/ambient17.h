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
 * @file ambient17.h
 * @brief This file contains API for Ambient 17 Click Driver.
 */

#ifndef AMBIENT17_H
#define AMBIENT17_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ambient17 Ambient 17 Click Driver
 * @brief API for configuring and manipulating Ambient 17 Click driver.
 * @{
 */

/**
 * @defgroup ambient17_reg Ambient 17 Registers List
 * @brief List of registers of Ambient 17 Click driver.
 */

/**
 * @addtogroup ambient17_reg
 * @{
 */

/**
 * @brief Ambient 17 registers list.
 * @details Specified registers list of Ambient 17 Click driver.
 */
#define AMBIENT17_REG_ENABLE                0x00
#define AMBIENT17_REG_ATIME                 0x01
#define AMBIENT17_REG_WTIME                 0x03
#define AMBIENT17_REG_AILTL                 0x04
#define AMBIENT17_REG_AILTH                 0x05
#define AMBIENT17_REG_AIHTL                 0x06
#define AMBIENT17_REG_AIHTH                 0x07
#define AMBIENT17_REG_PERS                  0x0C
#define AMBIENT17_REG_CONFIG                0x0D
#define AMBIENT17_REG_CONTROL               0x0F
#define AMBIENT17_REG_ID                    0x12
#define AMBIENT17_REG_STATUS                0x13
#define AMBIENT17_REG_C0DATA                0x14
#define AMBIENT17_REG_C0DATAH               0x15
#define AMBIENT17_REG_C1DATA                0x16
#define AMBIENT17_REG_C1DATAH               0x17

/*! @} */ // ambient17_reg

/**
 * @defgroup ambient17_set Ambient 17 Registers Settings
 * @brief Settings for registers of Ambient 17 Click driver.
 */

/**
 * @addtogroup ambient17_set
 * @{
 */

/**
 * @brief Ambient 17 command register setting.
 * @details Specified setting for Command register of Ambient 17 Click driver.
 */
#define AMBIENT17_CMD_BIT                   0x80
#define AMBIENT17_TYPE_REPEATED             0x00
#define AMBIENT17_TYPE_AUTO_INC             0x20
#define AMBIENT17_TYPE_SPEC_FUNC            0x60
#define AMBIENT17_SPEC_FUNC_INT_CLEAR       0x06

/**
 * @brief Ambient 17 enable register setting.
 * @details Specified setting for enable register of Ambient 17 Click driver.
 */
#define AMBIENT17_ENABLE_SLEEP_AFTER_INT    0x40
#define AMBIENT17_ENABLE_ALS_INT            0x10
#define AMBIENT17_ENABLE_WAIT               0x08
#define AMBIENT17_ENABLE_ALS                0x02
#define AMBIENT17_ENABLE_OSC                0x01

/**
 * @brief Ambient 17 status register setting.
 * @details Specified setting for status register of Ambient 17 Click driver.
 */
#define AMBIENT17_STATUS_AINT               0x10
#define AMBIENT17_STATUS_AVALID             0x01

/**
 * @brief Ambient 17 atime register setting.
 * @details Specified setting for atime register of Ambient 17 Click driver.
 */
#define AMBIENT17_ATIME_MAX                 699.88
#define AMBIENT17_ATIME_MIN                 2.73
#define AMBIENT17_ATIME_STEP                2.73
#define AMBIENT17_DEFAULT_ATIME             200.0

/**
 * @brief Ambient 17 wtime register setting.
 * @details Specified setting for wtime register of Ambient 17 Click driver.
 */
#define AMBIENT17_WTIME_MAX                 699.88
#define AMBIENT17_WTIME_MIN                 2.73
#define AMBIENT17_WTIME_STEP                2.73
#define AMBIENT17_DEFAULT_WTIME             200.0

/**
 * @brief Ambient 17 control register setting.
 * @details Specified setting for control register of Ambient 17 Click driver.
 */
#define AMBIENT17_AGAIN_1X                  0x00
#define AMBIENT17_AGAIN_8X                  0x01
#define AMBIENT17_AGAIN_16X                 0x02
#define AMBIENT17_AGAIN_120X                0x03

/**
 * @brief Ambient 17 lux calculation coefficients.
 * @details Specified lux calculation coefficients of Ambient 17 Click driver.
 */
#define AMBIENT17_CH0_COFF0                 1.0
#define AMBIENT17_CH1_COFF0                 1.87
#define AMBIENT17_CH0_COFF1                 0.63
#define AMBIENT17_CH1_COFF1                 1.0
#define AMBIENT17_GA_VALUE                  1.0
#define AMBIENT17_GA_MULTIPLIER             60.0

/**
 * @brief Ambient 17 ID values.
 * @details Specified ID values of Ambient 17 Click driver.
 */
#define AMBIENT17_DEVICE_ID                 0x34

/**
 * @brief Ambient 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 17 Click driver.
 */
#define AMBIENT17_DEVICE_ADDRESS            0x39

/*! @} */ // ambient17_set

/**
 * @defgroup ambient17_map Ambient 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 17 Click driver.
 */

/**
 * @addtogroup ambient17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 17 Click to the selected MikroBUS.
 */
#define AMBIENT17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient17_map
/*! @} */ // ambient17

/**
 * @brief Ambient 17 Click context object.
 * @details Context object definition of Ambient 17 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    
    float   atime_ms;               /**< ALS time in milliseconds. */
    uint8_t again;                  /**< ALS gain level. */
    float   cpl;                    /**< Counts per LUX value calculated when ATIME or AGAIN is changed. */

} ambient17_t;

/**
 * @brief Ambient 17 Click configuration object.
 * @details Configuration object definition of Ambient 17 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} ambient17_cfg_t;

/**
 * @brief Ambient 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT17_OK = 0,
    AMBIENT17_ERROR = -1

} ambient17_return_value_t;

/*!
 * @addtogroup ambient17 Ambient 17 Click Driver
 * @brief API for configuring and manipulating Ambient 17 Click driver.
 * @{
 */

/**
 * @brief Ambient 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient17_cfg_setup ( ambient17_cfg_t *cfg );

/**
 * @brief Ambient 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_init ( ambient17_t *ctx, ambient17_cfg_t *cfg );

/**
 * @brief Ambient 17 default configuration function.
 * @details This function executes a default configuration of Ambient 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient17_default_cfg ( ambient17_t *ctx );

/**
 * @brief Ambient 17 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_generic_write ( ambient17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Ambient 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_generic_read ( ambient17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Ambient 17 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_write_register ( ambient17_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Ambient 17 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_read_register ( ambient17_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Ambient 17 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_check_communication ( ambient17_t *ctx );

/**
 * @brief Ambient 17 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ambient17_get_int_pin ( ambient17_t *ctx );

/**
 * @brief Ambient 17 clear interrupts function.
 * @details This function clears all interrupts by sending the INT clear special function command.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_clear_interrupts ( ambient17_t *ctx );

/**
 * @brief Ambient 17 set atime function.
 * @details This function sets the ATIME register for the selected ALS integration time.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[in] atime_ms : Als integration time. Valid values from 2.73 to 699.88 milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_set_atime ( ambient17_t *ctx, float atime_ms );

/**
 * @brief Ambient 17 set wtime function.
 * @details This function sets the WTIME register for the selected wait time. 
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[in] wtime_ms : Wait time period. Valid values from 2.73 to 699.88 milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait time must be enabled in the ENABLE register.
 */
err_t ambient17_set_wtime ( ambient17_t *ctx, float wtime_ms );

/**
 * @brief Ambient 17 set again function.
 * @details This function sets the ALS gain level in the CONTROL register.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[in] again : ALS gain level
 *                    @li @c 0 - 1X,
 *                    @li @c 1 - 8X,
 *                    @li @c 2 - 16X,
 *                    @li @c 3 - 120X.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_set_again ( ambient17_t *ctx, uint8_t again );

/**
 * @brief Ambient 17 read raw data function.
 * @details This function checks if the data is ready and then reads the raw ADC data from two channels.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[out] ch_0 : Raw data from channel 0.
 * @param[out] ch_1 : Raw data from channel 1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_read_raw_data ( ambient17_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );

/**
 * @brief Ambient 17 measure light level function.
 * @details This function reads the raw ADC data from two channels and then measures the light
 * level in lux based on those readings.
 * @param[in] ctx : Click context object.
 * See #ambient17_t object definition for detailed explanation.
 * @param[out] lux : Ambient light level in Lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient17_measure_light_level ( ambient17_t *ctx, uint16_t *lux );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT17_H

/*! @} */ // ambient17

// ------------------------------------------------------------------------ END
