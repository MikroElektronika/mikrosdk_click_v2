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
 * @file uv5.h
 * @brief This file contains API for UV 5 Click Driver.
 */

#ifndef UV5_H
#define UV5_H

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
 * @addtogroup uv5 UV 5 Click Driver
 * @brief API for configuring and manipulating UV 5 Click driver.
 * @{
 */

/**
 * @defgroup uv5_reg UV 5 Registers List
 * @brief List of registers of UV 5 Click driver.
 */

/**
 * @addtogroup uv5_reg
 * @{
 */

/**
 * @brief UV 5 description register.
 * @details Specified register for description of UV 5 Click driver.
 */
#define UV5_CFG_STATE_REG_OSR                 0x00
#define UV5_CFG_STATE_REG_AGEN                0x02
#define UV5_CFG_STATE_REG_CREG1               0x06
#define UV5_CFG_STATE_REG_CREG2               0x07
#define UV5_CFG_STATE_REG_CREG3               0x08
#define UV5_CFG_STATE_REG_BREAK               0x09
#define UV5_CFG_STATE_REG_EDGES               0x0A
#define UV5_CFG_STATE_REG_OPTREG              0x0B
#define UV5_MESASURE_STATE_REG_OSR            0x00
#define UV5_MESASURE_STATE_REG_TEMP           0x01
#define UV5_MESASURE_STATE_REG_MRES1          0x02
#define UV5_MESASURE_STATE_REG_MRES2          0x03
#define UV5_MESASURE_STATE_REG_MRES3          0x04
#define UV5_MESASURE_STATE_REG_OUTCONV_L      0x05
#define UV5_MESASURE_STATE_REG_OUTCONV_H      0x06

/*! @} */ // uv5_reg

/**
 * @defgroup uv5_set UV 5 Registers Settings
 * @brief Settings for registers of UV 5 Click driver.
 */

/**
 * @addtogroup uv5_set
 * @{
 */

/**
 * @brief UV 5 description setting.
 * @details Specified setting for description of UV 5 Click driver.
 */

/**
 * @brief UV 5 OSR register setting.
 * @details Specified setting for OSR register of UV 5 Click driver.
 */
#define UV5_START_MEASURMENT                  0x80
#define UV5_POWER_DOWN                        0x40
#define UV5_SW_RESET                          0x08
#define UV5_CONFIGURATION_MODE                0x02
#define UV5_MEASUREMENT_MODE                  0x03

/**
 * @brief UV 5 AGEN register setting.
 * @details Specified setting for AGEN register of UV 5 Click driver.
 */
#define UV5_DEVID                             0x20
#define UV5_MUT                               0x01

/**
 * @brief UV 5 CREG1 register setting.
 * @details Specified setting for CREG1 register of UV 5 Click driver.
 */
#define UV5_GAIN_2048X                        0x00
#define UV5_GAIN_1024X                        0x10
#define UV5_GAIN_512X                         0x20
#define UV5_GAIN_256X                         0x30
#define UV5_GAIN_128X                         0x40
#define UV5_GAIN_64X                          0x50
#define UV5_GAIN_32X                          0x60
#define UV5_GAIN_16X                          0x70
#define UV5_GAIN_8X                           0x80
#define UV5_GAIN_4X                           0x90
#define UV5_GAIN_2X                           0xA0
#define UV5_GAIN_1X                           0xB0
#define UV5_TIME_1_MS                         0x00
#define UV5_TIME_2_MS                         0x01
#define UV5_TIME_4_MS                         0x02
#define UV5_TIME_8_MS                         0x03
#define UV5_TIME_16_MS                        0x04
#define UV5_TIME_32_MS                        0x05
#define UV5_TIME_64_MS                        0x06
#define UV5_TIME_128_MS                       0x07
#define UV5_TIME_256_MS                       0x08
#define UV5_TIME_512_MS                       0x09
#define UV5_TIME_1024_MS                      0x0A
#define UV5_TIME_2048_MS                      0x0B
#define UV5_TIME_4096_MS                      0x0C
#define UV5_TIME_8192_MS                      0x0D
#define UV5_TIME_16384_MS                     0x0E

/**
 * @brief UV 5 CREG2 register setting.
 * @details Specified setting for CREG2 register of UV 5 Click driver.
 */
#define UV5_EN_TM                             0x40
#define UV5_EN_DIV                            0x08
#define UV5_DIV_256                           0x07
#define UV5_DIV_128                           0x06
#define UV5_DIV_64                            0x05
#define UV5_DIV_32                            0x04
#define UV5_DIV_16                            0x03
#define UV5_DIV_8                             0x02
#define UV5_DIV_4                             0x01
#define UV5_DIV_2                             0x00

/**
 * @brief UV 5 CREG3 register setting.
 * @details Specified setting for CREG3 register of UV 5 Click driver.
 */
#define UV5_MMODE_CONT                        0x00
#define UV5_MMODE_CMD                         0x40
#define UV5_MMODE_SYNS                        0x80
#define UV5_MMODE_SYND                        0xC0
#define UV5_STANDBY_ON                        0x10
#define UV5_READY_PUSH_PULL                   0x00
#define UV5_READY_OPEN_DRAIN                  0x08
#define UV5_CCLK_1024_KHZ                     0x00
#define UV5_CCLK_2048_KHZ                     0x01
#define UV5_CCLK_4096_KHZ                     0x02
#define UV5_CCLK_8192_KHZ                     0x03

#define UV5_TEMPERATURE_CALC_CONST            0.05
#define UV5_TEMPERATURE_CALC_VALUE            66.9

/**
 * @brief UV 5 device address setting.
 * @details Specified setting for device slave address selection of
 * UV 5 Click driver.
 */
#define UV5_DEVICE_ADDRESS_00                  0x74
#define UV5_DEVICE_ADDRESS_01                  0x75
#define UV5_DEVICE_ADDRESS_10                  0x76
#define UV5_DEVICE_ADDRESS_11                  0x77

/*! @} */ // uv5_set

/**
 * @defgroup uv5_map UV 5 MikroBUS Map
 * @brief MikroBUS pin mapping of UV 5 Click driver.
 */

/**
 * @addtogroup uv5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UV 5 Click to the selected MikroBUS.
 */
#define UV5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.syn = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // uv5_map
/*! @} */ // uv5

/**
 * @brief UV 5 Click context object.
 * @details Context object definition of UV 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t syn;          /**< External controlled conversion pin. */

    // Input pins
    digital_in_t rdy;           /**< Ready pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} uv5_t;

/**
 * @brief UV 5 Click configuration object.
 * @details Configuration object definition of UV 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t syn;             /**< External controlled conversion pin. */
    pin_name_t rdy;             /**< Ready pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} uv5_cfg_t;

/**
 * @brief UV 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UV5_OK = 0,
    UV5_ERROR = -1

} uv5_return_value_t;

/*!
 * @addtogroup uv5 UV 5 Click Driver
 * @brief API for configuring and manipulating UV 5 Click driver.
 * @{
 */

/**
 * @brief UV 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uv5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uv5_cfg_setup ( uv5_cfg_t *cfg );

/**
 * @brief UV 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uv5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_init ( uv5_t *ctx, uv5_cfg_t *cfg );

/**
 * @brief UV 5 default configuration function.
 * @details This function executes a default configuration of UV 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t uv5_default_cfg ( uv5_t *ctx );

/**
 * @brief UV 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_generic_write ( uv5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief UV 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_generic_read ( uv5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );


/**
 * @brief UV 5 configuration mode register write function.
 * @details This function writes a bytes of data starting from
 * the selected register, when device is in configuration mode.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_write_cfg_reg ( uv5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief UV 5 measurement mode register write function.
 * @details This function writes a bytes of data starting from
 * the selected register, when device is in measurement mode.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_write_measu_reg ( uv5_t *ctx, uint8_t reg, uint8_t *data_in );

/**
 * @brief UV 5 configuration mode register reading function.
 * @details This function reads bytes of data starting from
 * the selected register in configuration mode by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_read_cfg_reg ( uv5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief UV 5 measurement mode register reading function.
 * @details This function reads bytes of data starting from
 * the selected register in measurement mode by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_read_measu_reg ( uv5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief UV 5 set SYN pin state function.
 * @details This function is used to set state of the SYN pin.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[in] pin_state : SYN pin state.
 * @return Nothing.
 * @note None.
 */
void uv5_set_syn_pin ( uv5_t *ctx, uint8_t pin_state );

/**
 * @brief UV 5 get READY pin state function.
 * @details This function is used to get state of the READY pin.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t uv5_get_rdy_pin ( uv5_t *ctx );

/**
 * @brief UV 5 software reset function.
 * @details This function is used to perform software reset.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_sw_reset ( uv5_t *ctx );

/**
 * @brief UV 5 read temperature function.
 * @details This function is used to read temperature.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[out] temp_data : Read temperature in degrees celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_temperature_read ( uv5_t *ctx, float *temp_data );

/**
 * @brief UV 5 read raw UVA data function.
 * @details This function is used to read raw UVA data.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[out] uva_data : Read raw UVA data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_channel_uva_read ( uv5_t *ctx, uint16_t *uva_data );

/**
 * @brief UV 5 read raw UVB data function.
 * @details This function is used to read raw UVB data.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[out] uva_data : Read raw UVB data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_channel_uvb_read ( uv5_t *ctx, uint16_t *uvb_data );

/**
 * @brief UV 5 read raw UVC data function.
 * @details This function is used to read raw UVC data.
 * @param[in] ctx : Click context object.
 * See #uv5_t object definition for detailed explanation.
 * @param[out] uva_data : Read raw UVC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uv5_channel_uvc_read ( uv5_t *ctx, uint16_t *uvc_data );

#ifdef __cplusplus
}
#endif
#endif // UV5_H

/*! @} */ // uv5

// ------------------------------------------------------------------------ END
