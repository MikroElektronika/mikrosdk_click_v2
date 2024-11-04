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
 * @file ambient15.h
 * @brief This file contains API for Ambient 15 Click Driver.
 */

#ifndef AMBIENT15_H
#define AMBIENT15_H

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
 * @addtogroup ambient15 Ambient 15 Click Driver
 * @brief API for configuring and manipulating Ambient 15 Click driver.
 * @{
 */

/**
 * @defgroup ambient15_reg Ambient 15 Registers List
 * @brief List of registers of Ambient 15 Click driver.
 */

/**
 * @addtogroup ambient15_reg
 * @{
 */

/**
 * @brief Ambient 15 registers list.
 * @details Specified registers list of Ambient 15 Click driver.
 */
#define AMBIENT15_REG_CONTROL               0x00
#define AMBIENT15_REG_TIMING                0x01
#define AMBIENT15_REG_INTERRUPT             0x02
#define AMBIENT15_REG_THL_LOW               0x03
#define AMBIENT15_REG_THL_HIGH              0x04
#define AMBIENT15_REG_THH_LOW               0x05
#define AMBIENT15_REG_THH_HIGH              0x06
#define AMBIENT15_REG_ANALOG                0x07
#define AMBIENT15_REG_ID                    0x12
#define AMBIENT15_REG_DATA0_LOW             0x14
#define AMBIENT15_REG_DATA0_HIGH            0x15
#define AMBIENT15_REG_DATA1_LOW             0x16
#define AMBIENT15_REG_DATA1_HIGH            0x17
#define AMBIENT15_REG_TIMER_LOW             0x18
#define AMBIENT15_REG_TIMER_HIGH            0x19
#define AMBIENT15_REG_ID2                   0x1E

/*! @} */ // ambient15_reg

/**
 * @defgroup ambient15_set Ambient 15 Registers Settings
 * @brief Settings for registers of Ambient 15 Click driver.
 */

/**
 * @addtogroup ambient15_set
 * @{
 */

/**
 * @brief Ambient 15 Command register setting.
 * @details Specified setting for Command register of Ambient 15 Click driver.
 */
#define AMBIENT15_CMD_BIT                   0x80
#define AMBIENT15_TRANSACTION_REPEATED      0x00
#define AMBIENT15_TRANSACTION_AUTO_INC      0x20
#define AMBIENT15_TRANSACTION_SPEC_FUNC     0x60
#define AMBIENT15_SPEC_FUNC_INT_CLEAR       0x01
#define AMBIENT15_SPEC_FUNC_STOP_MAN_INT    0x02
#define AMBIENT15_SPEC_FUNC_START_MAN_INT   0x03

/**
 * @brief Ambient 15 control register setting.
 * @details Specified setting for control register of Ambient 15 Click driver.
 */
#define AMBIENT15_CONTROL_ADC_INTR          0x20
#define AMBIENT15_CONTROL_ADC_VALID         0x10
#define AMBIENT15_CONTROL_ADC_ENABLE        0x02
#define AMBIENT15_CONTROL_POWER_ON          0x01

/**
 * @brief Ambient 15 timing register setting.
 * @details Specified setting for timing register of Ambient 15 Click driver.
 */
#define AMBIENT15_ATIME_MAX                 688.5
#define AMBIENT15_ATIME_MIN                 2.7
#define AMBIENT15_ATIME_STEP                2.7
#define AMBIENT15_DEFAULT_ATIME             200.0

/**
 * @brief Ambient 15 interrupt register setting.
 * @details Specified setting for interrupt register of Ambient 15 Click driver.
 */
#define AMBIENT15_ENABLE_INTERRUPT          0x10

/**
 * @brief Ambient 15 analog register setting.
 * @details Specified setting for analog register of Ambient 15 Click driver.
 */
#define AMBIENT15_GAIN_1X                   0x00
#define AMBIENT15_GAIN_8X                   0x01
#define AMBIENT15_GAIN_16X                  0x02
#define AMBIENT15_GAIN_111X                 0x03

/**
 * @brief Ambient 15 ID values.
 * @details Specified ID values of Ambient 15 Click driver.
 */
#define AMBIENT15_ID_PARTNO                 0x90
#define AMBIENT15_ID2                       0x80

/**
 * @brief Ambient 15 lux calculation coefficients.
 * @details Specified lux calculation coefficients of Ambient 15 Click driver.
 */
#define AMBIENT15_CH0_COFF0                 1000ul
#define AMBIENT15_CH1_COFF0                 2160ul
#define AMBIENT15_CH0_COFF1                 950ul
#define AMBIENT15_CH1_COFF1                 1110ul

/**
 * @brief Ambient 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 15 Click driver.
 */
#define AMBIENT15_SET_DEV_ADDR_GND          0x29
#define AMBIENT15_SET_DEV_ADDR_FLOAT        0x39
#define AMBIENT15_SET_DEV_ADDR_VCC          0x49

/*! @} */ // ambient15_set

/**
 * @defgroup ambient15_map Ambient 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 15 Click driver.
 */

/**
 * @addtogroup ambient15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 15 Click to the selected MikroBUS.
 */
#define AMBIENT15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient15_map
/*! @} */ // ambient15

/**
 * @brief Ambient 15 Click context object.
 * @details Context object definition of Ambient 15 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin (Active low). */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    float   atime_ms;           /**< ALS time in milliseconds. */
    uint8_t gain;               /**< Gain level. */

} ambient15_t;

/**
 * @brief Ambient 15 Click configuration object.
 * @details Configuration object definition of Ambient 15 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} ambient15_cfg_t;

/**
 * @brief Ambient 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT15_OK = 0,
    AMBIENT15_ERROR = -1

} ambient15_return_value_t;

/*!
 * @addtogroup ambient15 Ambient 15 Click Driver
 * @brief API for configuring and manipulating Ambient 15 Click driver.
 * @{
 */

/**
 * @brief Ambient 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient15_cfg_setup ( ambient15_cfg_t *cfg );

/**
 * @brief Ambient 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_init ( ambient15_t *ctx, ambient15_cfg_t *cfg );

/**
 * @brief Ambient 15 default configuration function.
 * @details This function executes a default configuration of Ambient 15
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient15_default_cfg ( ambient15_t *ctx );

/**
 * @brief Ambient 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_generic_write ( ambient15_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Ambient 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_generic_read ( ambient15_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Ambient 15 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_write_register ( ambient15_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Ambient 15 read register function.
 * @details This function reads a desired data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_read_register ( ambient15_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Ambient 15 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ambient15_get_int_pin ( ambient15_t *ctx );

/**
 * @brief Ambient 15 check communication function.
 * @details This function checks the communication by reading and verifying the chip ID values.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_check_communication ( ambient15_t *ctx );

/**
 * @brief Ambient 15 set atime function.
 * @details This function sets the timing register for the selected integration time.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[in] atime_ms : Als integration time. Valid values from 2.7 to 688.5 milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_set_atime ( ambient15_t *ctx, float atime_ms );

/**
 * @brief Ambient 15 set gain function.
 * @details This function sets the gain level.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[in] gain : Gain level value [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_set_gain ( ambient15_t *ctx, uint8_t gain );

/**
 * @brief Ambient 15 read raw data function.
 * @details This function checks if the data is ready and then reads the raw ADC data from two channels.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[out] ch_0 : Raw data from channel 0.
 * @param[out] ch_1 : Raw data from channel 1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_read_raw_data ( ambient15_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );

/**
 * @brief Ambient 15 measure light level function.
 * @details This function reads the raw ADC data from two channels and then measures the light
 * level in lux based on those readings.
 * @param[in] ctx : Click context object.
 * See #ambient15_t object definition for detailed explanation.
 * @param[out] lux : Ambient light level in Lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient15_measure_light_level ( ambient15_t *ctx, uint16_t *lux );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT15_H

/*! @} */ // ambient15

// ------------------------------------------------------------------------ END
