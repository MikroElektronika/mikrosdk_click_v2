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
 * @file adac3.h
 * @brief This file contains API for ADAC 3 Click Driver.
 */

#ifndef ADAC3_H
#define ADAC3_H

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
 * @addtogroup adac3 ADAC 3 Click Driver
 * @brief API for configuring and manipulating ADAC 3 Click driver.
 * @{
 */

/**
 * @defgroup adac3_set ADAC 3 Registers Settings
 * @brief Settings for registers of ADAC 3 Click driver.
 */

/**
 * @addtogroup adac3_set
 * @{
 */

/**
 * @brief ADAC 3 control byte settings.
 * @details Specified control byte settings of ADAC 3 Click driver.
 */
#define ADAC3_CONTROL_AOUT_ENABLE           0x40
#define ADAC3_CONTROL_AIN_SINGLE_ENDED      0x00
#define ADAC3_CONTROL_AIN_3_DIFFERENTIAL    0x10
#define ADAC3_CONTROL_AIN_MIXED             0x20
#define ADAC3_CONTROL_AIN_2_DIFFERENTIAL    0x30
#define ADAC3_CONTROL_AUTO_INCREMENT        0x04
#define ADAC3_CONTROL_AD_CH0                0x00
#define ADAC3_CONTROL_AD_CH1                0x01
#define ADAC3_CONTROL_AD_CH2                0x02
#define ADAC3_CONTROL_AD_CH3                0x03

/**
 * @brief ADAC 3 calculation values.
 * @details Specified calculation values of ADAC 3 Click driver.
 */
#define ADAC3_VREF_2048mV                   2048.0
#define ADAC3_VREF_4096mV                   4096.0
#define ADAC3_RESOLUTION                    0xFF

/**
 * @brief ADAC 3 device address setting.
 * @details Specified setting for device slave address selection of
 * ADAC 3 Click driver.
 */
#define ADAC3_DEVICE_ADDRESS_A2A1A0_000     0x48
#define ADAC3_DEVICE_ADDRESS_A2A1A0_001     0x49
#define ADAC3_DEVICE_ADDRESS_A2A1A0_010     0x4A
#define ADAC3_DEVICE_ADDRESS_A2A1A0_011     0x4B
#define ADAC3_DEVICE_ADDRESS_A2A1A0_100     0x4C
#define ADAC3_DEVICE_ADDRESS_A2A1A0_101     0x4D
#define ADAC3_DEVICE_ADDRESS_A2A1A0_110     0x4E
#define ADAC3_DEVICE_ADDRESS_A2A1A0_111     0x4F

/*! @} */ // adac3_set

/**
 * @defgroup adac3_map ADAC 3 MikroBUS Map
 * @brief MikroBUS pin mapping of ADAC 3 Click driver.
 */

/**
 * @addtogroup adac3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADAC 3 Click to the selected MikroBUS.
 */
#define ADAC3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // adac3_map
/*! @} */ // adac3

/**
 * @brief ADAC 3 Click context object.
 * @details Context object definition of ADAC 3 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t control;            /**< Control byte. */
    uint8_t dac;                /**< DAC byte. */

} adac3_t;

/**
 * @brief ADAC 3 Click configuration object.
 * @details Configuration object definition of ADAC 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} adac3_cfg_t;

/**
 * @brief ADAC 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADAC3_OK = 0,
    ADAC3_ERROR = -1

} adac3_return_value_t;

/*!
 * @addtogroup adac3 ADAC 3 Click Driver
 * @brief API for configuring and manipulating ADAC 3 Click driver.
 * @{
 */

/**
 * @brief ADAC 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adac3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adac3_cfg_setup ( adac3_cfg_t *cfg );

/**
 * @brief ADAC 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adac3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adac3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adac3_init ( adac3_t *ctx, adac3_cfg_t *cfg );

/**
 * @brief ADAC 3 default configuration function.
 * @details This function executes a default configuration of ADAC 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #adac3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adac3_default_cfg ( adac3_t *ctx );

/**
 * @brief ADAC 3 write control function.
 * @details This function writes a control byte by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adac3_t object definition for detailed explanation.
 * @param[in] control : Control byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't affect DAC value.
 */
err_t adac3_write_control ( adac3_t *ctx, uint8_t control );

/**
 * @brief ADAC 3 write dac function.
 * @details This function writes a DAC byte by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adac3_t object definition for detailed explanation.
 * @param[in] dac : DAC value [0-255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't affect control byte.
 */
err_t adac3_write_dac ( adac3_t *ctx, uint8_t dac );

/**
 * @brief ADAC 3 read adc function.
 * @details This function reads the AD conversion byte by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adac3_t object definition for detailed explanation.
 * @param[out] adc : AD conversion byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adac3_read_adc ( adac3_t *ctx, uint8_t *adc );

#ifdef __cplusplus
}
#endif
#endif // ADAC3_H

/*! @} */ // adac3

// ------------------------------------------------------------------------ END
