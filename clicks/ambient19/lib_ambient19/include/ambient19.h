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
 * @file ambient19.h
 * @brief This file contains API for Ambient 19 Click Driver.
 */

#ifndef AMBIENT19_H
#define AMBIENT19_H

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
 * @addtogroup ambient19 Ambient 19 Click Driver
 * @brief API for configuring and manipulating Ambient 19 Click driver.
 * @{
 */

/**
 * @defgroup ambient19_reg Ambient 19 Registers List
 * @brief List of registers of Ambient 19 Click driver.
 */

/**
 * @addtogroup ambient19_reg
 * @{
 */

/**
 * @brief Ambient 19 registers list.
 * @details Specified registers list of Ambient 19 Click driver.
 */
#define AMBIENT19_REG_SYSM_CTRL                 0x00
#define AMBIENT19_REG_INT_CTRL                  0x01
#define AMBIENT19_REG_INT_FLAG                  0x02
#define AMBIENT19_REG_WAIT_TIME                 0x03
#define AMBIENT19_REG_ALS_GAIN                  0x04
#define AMBIENT19_REG_ALS_TIME                  0x05
#define AMBIENT19_REG_LED_CTRL                  0x06
#define AMBIENT19_REG_PS_GAIN                   0x07
#define AMBIENT19_REG_PS_PULSE                  0x08
#define AMBIENT19_REG_PS_TIME                   0x09
#define AMBIENT19_REG_PERSISTENCE               0x0B
#define AMBIENT19_REG_ALS_THRES_LL              0x0C
#define AMBIENT19_REG_ALS_THRES_LH              0x0D
#define AMBIENT19_REG_ALS_THRES_HL              0x0E
#define AMBIENT19_REG_ALS_THRES_HH              0x0F
#define AMBIENT19_REG_PS_THRES_LL               0x10
#define AMBIENT19_REG_PS_THRES_LH               0x11
#define AMBIENT19_REG_PS_THRES_HL               0x12
#define AMBIENT19_REG_PS_THRES_HH               0x13
#define AMBIENT19_REG_PS_OFFSET_L               0x14
#define AMBIENT19_REG_PS_OFFSET_H               0x15
#define AMBIENT19_REG_INT_SOURCE                0x16
#define AMBIENT19_REG_ERROR_FLAG                0x17
#define AMBIENT19_REG_PS_DATA_L                 0x18
#define AMBIENT19_REG_PS_DATA_H                 0x19
#define AMBIENT19_REG_IR_DATA_L                 0x1A
#define AMBIENT19_REG_IR_DATA_H                 0x1B
#define AMBIENT19_REG_CH0_DATA_L                0x1C
#define AMBIENT19_REG_CH0_DATA_H                0x1D
#define AMBIENT19_REG_CH1_DATA_L                0x1E
#define AMBIENT19_REG_CH1_DATA_H                0x1F
#define AMBIENT19_REG_PNO_LB                    0xBC
#define AMBIENT19_REG_PNO_HB                    0xBD

/*! @} */ // ambient19_reg

/**
 * @defgroup ambient19_set Ambient 19 Registers Settings
 * @brief Settings for registers of Ambient 19 Click driver.
 */

/**
 * @addtogroup ambient19_set
 * @{
 */

/**
 * @brief Ambient 19 system control register settings.
 * @details Specified system control register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_SYSM_CTRL_SWRST               0x80
#define AMBIENT19_SYSM_EN_WAIT                  0x40
#define AMBIENT19_SYSM_EN_PS                    0x02
#define AMBIENT19_SYSM_EN_ALS                   0x01

/**
 * @brief Ambient 19 interrupt pin control register settings.
 * @details Specified interrupt pin control register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_INT_CTRL_PS_INT_MODE          0x80
#define AMBIENT19_INT_CTRL_SINT_MODE            0x40
#define AMBIENT19_INT_CTRL_PS_SYNC              0x20
#define AMBIENT19_INT_CTRL_ALS_SYNC             0x10
#define AMBIENT19_INT_CTRL_EN_PINT              0x02
#define AMBIENT19_INT_CTRL_EN_AINT              0x01

/**
 * @brief Ambient 19 interrupt flag register settings.
 * @details Specified interrupt flag register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_INT_FLAG_INT_POR              0x80
#define AMBIENT19_INT_FLAG_DATA_FLAG            0x40
#define AMBIENT19_INT_FLAG_OBJ                  0x20
#define AMBIENT19_INT_FLAG_INT_PS               0x02
#define AMBIENT19_INT_FLAG_INT_ALS              0x01

/**
 * @brief Ambient 19 wait time register settings.
 * @details Specified wait time register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_WAIT_TIME_MAX                 1280.0
#define AMBIENT19_WAIT_TIME_MIN                 5.0
#define AMBIENT19_WAIT_TIME_STEP                5.0
#define AMBIENT19_WAIT_TIME_DEFAULT             100.0

/**
 * @brief Ambient 19 als gain register settings.
 * @details Specified als gain register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_ALS_GAIN_1X                   0x00
#define AMBIENT19_ALS_GAIN_4X                   0x01
#define AMBIENT19_ALS_GAIN_8X                   0x02
#define AMBIENT19_ALS_GAIN_32X                  0x03
#define AMBIENT19_ALS_GAIN_96X                  0x04

/**
 * @brief Ambient 19 als time register settings.
 * @details Specified als time register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_ALS_TIME_MAX                  674.888
#define AMBIENT19_ALS_TIME_MIN                  5.513
#define AMBIENT19_ALS_TIME_STEP                 2.625
#define AMBIENT19_ALS_TIME_DEFAULT              400.0

/**
 * @brief Ambient 19 led control register settings.
 * @details Specified led control register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_LED_CTRL_IRDR_SEL_50mA        0x00
#define AMBIENT19_LED_CTRL_IRDR_SEL_100mA       0x40
#define AMBIENT19_LED_CTRL_IRDR_SEL_150mA       0x80
#define AMBIENT19_LED_CTRL_IRDR_SEL_200mA       0xC0
#define AMBIENT19_LED_CTRL_IRDR_SEL_BIT_MASK    0xC0
#define AMBIENT19_LED_CTRL_ITW_PS_MAX           875.213
#define AMBIENT19_LED_CTRL_ITW_PS_MIN           13.675
#define AMBIENT19_LED_CTRL_ITW_PS_STEP          13.675
#define AMBIENT19_LED_CTRL_ITW_PS_BIT_MASK      0x3F

/**
 * @brief Ambient 19 ps gain register settings.
 * @details Specified ps gain register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_PS_GAIN_1X                    0x00
#define AMBIENT19_PS_GAIN_2X                    0x01
#define AMBIENT19_PS_GAIN_4X                    0x02
#define AMBIENT19_PS_GAIN_8X                    0x03

/**
 * @brief Ambient 19 ps time register settings.
 * @details Specified ps time register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_PS_TIME_MAX_COUNT_4095        0x0F

/**
 * @brief Ambient 19 persistance register settings.
 * @details Specified persistance register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_PERSISTANCE_EVERY_ALS_CONV    0x00

/**
 * @brief Ambient 19 int source register settings.
 * @details Specified int source register settings of Ambient 19 Click driver.
 */
#define AMBIENT19_INT_SOURCE_CH0_DATA           0x00
#define AMBIENT19_INT_SOURCE_CH1_DATA           0x01

/**
 * @brief Ambient 19 lux calculation coefficients.
 * @details Specified lux calculation coefficients of Ambient 19 Click driver.
 */
#define AMBIENT19_LUX_K1                        0.52
#define AMBIENT19_LUX_K2                        0.94
#define AMBIENT19_LUX_K3                        1.12 // calculated using lux meter

/**
 * @brief Ambient 19 product number values.
 * @details Specified product number values of Ambient 19 Click driver.
 */
#define AMBIENT19_PRODUCT_NUM_LOW               0x14
#define AMBIENT19_PRODUCT_NUM_HIGH              0x16

/**
 * @brief Ambient 19 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 19 Click driver.
 */
#define AMBIENT19_DEVICE_ADDRESS                0x38

/*! @} */ // ambient19_set

/**
 * @defgroup ambient19_map Ambient 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 19 Click driver.
 */

/**
 * @addtogroup ambient19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 19 Click to the selected MikroBUS.
 */
#define AMBIENT19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient19_map
/*! @} */ // ambient19

/**
 * @brief Ambient 19 Click context object.
 * @details Context object definition of Ambient 19 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    
    uint8_t pga_als;                /**< ALS gain level. */
    uint8_t alsconv;                /**< ALS time register value. */

} ambient19_t;

/**
 * @brief Ambient 19 Click configuration object.
 * @details Configuration object definition of Ambient 19 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} ambient19_cfg_t;

/**
 * @brief Ambient 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT19_OK = 0,
    AMBIENT19_ERROR = -1

} ambient19_return_value_t;

/*!
 * @addtogroup ambient19 Ambient 19 Click Driver
 * @brief API for configuring and manipulating Ambient 19 Click driver.
 * @{
 */

/**
 * @brief Ambient 19 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient19_cfg_setup ( ambient19_cfg_t *cfg );

/**
 * @brief Ambient 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_init ( ambient19_t *ctx, ambient19_cfg_t *cfg );

/**
 * @brief Ambient 19 default configuration function.
 * @details This function executes a default configuration of Ambient 19
 * click board.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient19_default_cfg ( ambient19_t *ctx );

/**
 * @brief Ambient 19 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_generic_write ( ambient19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Ambient 19 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_generic_read ( ambient19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Ambient 19 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_write_register ( ambient19_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Ambient 19 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_read_register ( ambient19_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Ambient 19 check communication function.
 * @details This function checks the communication by reading and verifying the product number.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_check_communication ( ambient19_t *ctx );

/**
 * @brief Ambient 19 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ambient19_get_int_pin ( ambient19_t *ctx );

/**
 * @brief Ambient 19 clear interrupts function.
 * @details This function clears all interrupts by clearing the INT_FLAG register.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_clear_interrupts ( ambient19_t *ctx );

/**
 * @brief Ambient 19 set wait time function.
 * @details This function sets the WAIT_TIME register for the selected wait time. 
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[in] wait_time_ms : Wait time period. Valid values from 5.0 to 1280.0 milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait time must be enabled in the SYSM_CTRL register.
 */
err_t ambient19_set_wait_time ( ambient19_t *ctx, float wait_time_ms );

/**
 * @brief Ambient 19 set als time function.
 * @details This function sets the ALS_TIME register for the selected ALS integration time.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[in] als_time_ms : Als integration time. Valid values from 5.513 to 674.888 milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_set_als_time ( ambient19_t *ctx, float als_time_ms );

/**
 * @brief Ambient 19 set als gain function.
 * @details This function sets the ALS gain level in the ALS_GAIN register.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[in] als_gain : ALS gain level
 *                       @li @c 0 - 1X,
 *                       @li @c 1 - 4X,
 *                       @li @c 2 - 8X,
 *                       @li @c 3 - 32X.
 *                       @li @c 4 - 96X.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_set_als_gain ( ambient19_t *ctx, uint8_t als_gain );

/**
 * @brief Ambient 19 read raw als function.
 * @details This function reads the raw ALS data from two channels.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[out] ch_0 : Raw data from channel 0.
 * @param[out] ch_1 : Raw data from channel 1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_read_raw_als ( ambient19_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );

/**
 * @brief Ambient 19 read raw proximity function.
 * @details This function reads the raw PS and IR data of the proximity sensor.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[out] ps_data : Raw PS data.
 * @param[out] ir_data : Raw IR data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_read_raw_proximity ( ambient19_t *ctx, uint16_t *ps_data, uint16_t *ir_data );

/**
 * @brief Ambient 19 measure light level function.
 * @details This function reads the raw ALS data from two channels and then measures the light
 * level in lux based on those readings.
 * @param[in] ctx : Click context object.
 * See #ambient19_t object definition for detailed explanation.
 * @param[out] lux : Ambient light level in Lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient19_measure_light_level ( ambient19_t *ctx, uint16_t *lux );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT19_H

/*! @} */ // ambient19

// ------------------------------------------------------------------------ END
