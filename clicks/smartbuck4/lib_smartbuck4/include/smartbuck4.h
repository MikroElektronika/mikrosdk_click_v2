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
 * @file smartbuck4.h
 * @brief This file contains API for Smart Buck 4 Click Driver.
 */

#ifndef SMARTBUCK4_H
#define SMARTBUCK4_H

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
 * @addtogroup smartbuck4 Smart Buck 4 Click Driver
 * @brief API for configuring and manipulating Smart Buck 4 Click driver.
 * @{
 */

/**
 * @defgroup smartbuck4_reg Smart Buck 4 Registers List
 * @brief List of registers of Smart Buck 4 Click driver.
 */

/**
 * @addtogroup smartbuck4_reg
 * @{
 */

/**
 * @brief Smart Buck 4 description register.
 * @details Specified register for description of Smart Buck 4 Click driver.
 */
#define SMARTBUCK4_REG_R600A_PROGRAM            0x80
#define SMARTBUCK4_REG_R400A_PROGRAM            0x40
#define SMARTBUCK4_REG_R600B_PROGRAM            0x20
#define SMARTBUCK4_REG_R400B_PROGRAM            0x10
#define SMARTBUCK4_REG_PULSE_SKIP_MODE          0x00
#define SMARTBUCK4_REG_LDO_MODE                 0x01
#define SMARTBUCK4_REG_FORCED_BURST_MODE        0x02
#define SMARTBUCK4_REG_BURST_MODE               0x03

/*! @} */ // smartbuck4_reg

/**
 * @defgroup smartbuck4_set Smart Buck 4 Registers Settings
 * @brief Settings for registers of Smart Buck 4 Click driver.
 */

/**
 * @addtogroup smartbuck4_set
 * @{
 */

/**
 * @brief Smart Buck 4 description setting.
 * @details Specified setting for description of Smart Buck 4 Click driver.
 */
#define SMARTBUCK4_PIN_STATE_LOW                0x00
#define SMARTBUCK4_PIN_STATE_HIGH               0x01

/**
 * @brief Smart Buck 4 regulator setting.
 * @details Specified setting for regulator of Smart Buck 4 Click driver.
 */
#define SMARTBUCK4_ENABLE_REGULATOR             0x80
#define SMARTBUCK4_DISABLE_REGULATOR            0x00

/**
 * @brief Smart Buck 4 Type-A regulator servo (feedback) voltage setting.
 * @details Specified setting for Type-A regulator servo (feedback) voltage of
 * Smart Buck 4 Click driver.
 */
#define SMARTBUCK4_REGULATOR_A_FB_425_MV        0x00
#define SMARTBUCK4_REGULATOR_A_FB_450_MV        0x01
#define SMARTBUCK4_REGULATOR_A_FB_475_MV        0x02
#define SMARTBUCK4_REGULATOR_A_FB_500_MV        0x03
#define SMARTBUCK4_REGULATOR_A_FB_525_MV        0x04
#define SMARTBUCK4_REGULATOR_A_FB_550_MV        0x05
#define SMARTBUCK4_REGULATOR_A_FB_575_MV        0x06
#define SMARTBUCK4_REGULATOR_A_FB_600_MV        0x07
#define SMARTBUCK4_REGULATOR_A_FB_625_MV        0x08
#define SMARTBUCK4_REGULATOR_A_FB_650_MV        0x09
#define SMARTBUCK4_REGULATOR_A_FB_675_MV        0x0A
#define SMARTBUCK4_REGULATOR_A_FB_700_MV        0x0B
#define SMARTBUCK4_REGULATOR_A_FB_725_MV        0x0C
#define SMARTBUCK4_REGULATOR_A_FB_750_MV        0x0D
#define SMARTBUCK4_REGULATOR_A_FB_775_MV        0x0E
#define SMARTBUCK4_REGULATOR_A_FB_800_MV        0x0F

/**
 * @brief Smart Buck 4 Type-B regulator base output voltage setting.
 * @details Specified setting for Type-B regulator base output voltage of
 * Smart Buck 4 Click driver.
 */
#define SMARTBUCK4_REGULATOR_B_600_MV           0x00
#define SMARTBUCK4_REGULATOR_B_700_MV           0x04
#define SMARTBUCK4_REGULATOR_B_800_MV           0x08
#define SMARTBUCK4_REGULATOR_B_900_MV           0x0C
#define SMARTBUCK4_REGULATOR_B_1000_MV          0x10
#define SMARTBUCK4_REGULATOR_B_1100_MV          0x14
#define SMARTBUCK4_REGULATOR_B_1200_MV          0x18
#define SMARTBUCK4_REGULATOR_B_1300_MV          0x1C
#define SMARTBUCK4_REGULATOR_B_1400_MV          0x20
#define SMARTBUCK4_REGULATOR_B_1500_MV          0x24
#define SMARTBUCK4_REGULATOR_B_1600_MV          0x28
#define SMARTBUCK4_REGULATOR_B_1700_MV          0x2C
#define SMARTBUCK4_REGULATOR_B_1800_MV          0x30
#define SMARTBUCK4_REGULATOR_B_1900_MV          0x34
#define SMARTBUCK4_REGULATOR_B_2000_MV          0x38
#define SMARTBUCK4_REGULATOR_B_2100_MV          0x3C
#define SMARTBUCK4_REGULATOR_B_2200_MV          0x40
#define SMARTBUCK4_REGULATOR_B_2300_MV          0x44
#define SMARTBUCK4_REGULATOR_B_2400_MV          0x48
#define SMARTBUCK4_REGULATOR_B_2500_MV          0x4C
#define SMARTBUCK4_REGULATOR_B_2600_MV          0x50
#define SMARTBUCK4_REGULATOR_B_2700_MV          0x54
#define SMARTBUCK4_REGULATOR_B_2800_MV          0x58
#define SMARTBUCK4_REGULATOR_B_2900_MV          0x5C
#define SMARTBUCK4_REGULATOR_B_3000_MV          0x60
#define SMARTBUCK4_REGULATOR_B_3100_MV          0x64
#define SMARTBUCK4_REGULATOR_B_3200_MV          0x68
#define SMARTBUCK4_REGULATOR_B_3300_MV          0x6C
#define SMARTBUCK4_REGULATOR_B_3400_MV          0x70
#define SMARTBUCK4_REGULATOR_B_3500_MV          0x74
#define SMARTBUCK4_REGULATOR_B_3600_MV          0x78
#define SMARTBUCK4_REGULATOR_B_3700_MV          0x7C

/**
 * @brief Smart Buck 4 Type-B regulator incremental output voltage setting.
 * @details Specified setting for Type-B regulator incremental output voltage of
 * Smart Buck 4 Click driver.
 */
#define SMARTBUCK4_REGULATOR_B_INC_0_MV         0x00
#define SMARTBUCK4_REGULATOR_B_INC_25_MV        0x01
#define SMARTBUCK4_REGULATOR_B_INC_50_MV        0x02
#define SMARTBUCK4_REGULATOR_B_INC_75_MV        0x03

/**
 * @brief Smart Buck 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Buck 4 Click driver.
 */
#define SMARTBUCK4_DEVICE_ADDRESS               0x65

/*! @} */ // smartbuck4_set

/**
 * @defgroup smartbuck4_map Smart Buck 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Buck 4 Click driver.
 */

/**
 * @addtogroup smartbuck4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Buck 4 Click to the selected MikroBUS.
 */
#define SMARTBUCK4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.r40 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.r60 = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // smartbuck4_map
/*! @} */ // smartbuck4

/**
 * @brief Smart Buck 4 Click context object.
 * @details Context object definition of Smart Buck 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t r40;              /**< Enable R400A regulator pin. */
    digital_out_t r60;              /**< Enable R600A regulator pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} smartbuck4_t;

/**
 * @brief Smart Buck 4 Click configuration object.
 * @details Configuration object definition of Smart Buck 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t r40;             /**< Enable R400A regulator pin. */
    pin_name_t r60;             /**< Enable R600A regulator pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} smartbuck4_cfg_t;

/**
 * @brief Smart Buck 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTBUCK4_OK = 0,
    SMARTBUCK4_ERROR = -1

} smartbuck4_return_value_t;

/*!
 * @addtogroup smartbuck4 Smart Buck 4 Click Driver
 * @brief API for configuring and manipulating Smart Buck 4 Click driver.
 * @{
 */

/**
 * @brief Smart Buck 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartbuck4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartbuck4_cfg_setup ( smartbuck4_cfg_t *cfg );

/**
 * @brief Smart Buck 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartbuck4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck4_init ( smartbuck4_t *ctx, smartbuck4_cfg_t *cfg );

/**
 * @brief Smart Buck 4 default configuration function.
 * @details This function executes a default configuration of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartbuck4_default_cfg ( smartbuck4_t *ctx );

/**
 * @brief Smart Buck 4 set R40 pin state function.
 * @details This function is used to set R40 pin value of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @param[in] out_level : Pin output value.
 * @return Nothing.
 * @note None.
 */
void smartbuck4_set_r40_out ( smartbuck4_t *ctx, uint8_t out_level );

/**
 * @brief Smart Buck 4 enable 400A regulator function.
 * @details This function is used to enable 400A regulator of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void smartbuck4_en_r40_reg ( smartbuck4_t *ctx );

/**
 * @brief Smart Buck 4 disable 400A regulator function.
 * @details This function is used to disable 400A regulator of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void smartbuck4_dis_r40_reg ( smartbuck4_t *ctx );

/**
 * @brief Smart Buck 4 set R60 pin state function.
 * @details This function is used to set R60 pin value of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @param[in] out_level : Pin output value.
 * @return Nothing.
 * @note None.
 */
void smartbuck4_set_r60_out ( smartbuck4_t *ctx, uint8_t out_level );

/**
 * @brief Smart Buck 4 enable 600A regulator function.
 * @details This function is used to enable 600A regulator of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void smartbuck4_en_r60_reg ( smartbuck4_t *ctx );

/**
 * @brief Smart Buck 4 disable 600A regulator function.
 * @details This function is used to disable 600A regulator of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void smartbuck4_dis_r60_reg ( smartbuck4_t *ctx );

/**
 * @brief Smart Buck 4 send command function.
 * @details This function is used to send a specific command of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @param[in] addr : Specific sub-address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck4_send_command ( smartbuck4_t *ctx, uint8_t addr, uint8_t data_in );

/**
 * @brief Smart Buck 4 disable regulators function.
 * @details This function is used to disable regulator output of Smart Buck 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck4_disable_regulators ( smartbuck4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SMARTBUCK4_H

/*! @} */ // smartbuck4

// ------------------------------------------------------------------------ END
