/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file proximity25.h
 * @brief This file contains API for Proximity 25 Click Driver.
 */

#ifndef PROXIMITY25_H
#define PROXIMITY25_H

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
 * @addtogroup proximity25 Proximity 25 Click Driver
 * @brief API for configuring and manipulating Proximity 25 Click driver.
 * @{
 */

/**
 * @defgroup proximity25_reg Proximity 25 Registers List
 * @brief List of registers of Proximity 25 Click driver.
 */

/**
 * @addtogroup proximity25_reg
 * @{
 */

/**
 * @brief Proximity 25 registers list.
 * @details Specified registers list of Proximity 25 Click driver.
 */
#define PROXIMITY25_REG_PS_CONF1                0x00
#define PROXIMITY25_REG_PS_CONF2                0x03
#define PROXIMITY25_REG_PS_CONF3                0x04
#define PROXIMITY25_REG_PS_THDL                 0x05
#define PROXIMITY25_REG_PS_THDH                 0x06
#define PROXIMITY25_REG_PS_CANC                 0x07
#define PROXIMITY25_REG_PS_DATA                 0xF4
#define PROXIMITY25_REG_INT_FLAG                0xF5
#define PROXIMITY25_REG_ID                      0xF6

/*! @} */ // proximity25_reg

/**
 * @defgroup proximity25_set Proximity 25 Registers Settings
 * @brief Settings for registers of Proximity 25 Click driver.
 */

/**
 * @addtogroup proximity25_set
 * @{
 */

/**
 * @brief Proximity 25 PS_CONF1 register settings.
 * @details Specified PS_CONF1 register settings of Proximity 25 Click driver.
 */
#define PROXIMITY25_PS_CONF1_PS_CAL_DIS         0x0000
#define PROXIMITY25_PS_CONF1_PS_CAL_EN          0x0080
#define PROXIMITY25_PS_CONF1_PS_CAL_MASK        0x0080
#define PROXIMITY25_PS_CONF1_PS_ON_DIS          0x0000
#define PROXIMITY25_PS_CONF1_PS_ON_EN           0x0002
#define PROXIMITY25_PS_CONF1_PS_ON_MASK         0x0002
#define PROXIMITY25_PS_CONF1_RESERVED           0x0201

/**
 * @brief Proximity 25 PS_CONF2 register settings.
 * @details Specified PS_CONF2 register settings of Proximity 25 Click driver.
 */
#define PROXIMITY25_PS_CONF2_PS_IT_1T           0x0000
#define PROXIMITY25_PS_CONF2_PS_IT_2T           0x4000
#define PROXIMITY25_PS_CONF2_PS_IT_4T           0x8000
#define PROXIMITY25_PS_CONF2_PS_IT_8T           0xC000
#define PROXIMITY25_PS_CONF2_PS_IT_MASK         0xC000
#define PROXIMITY25_PS_CONF2_PS_MPS_1           0x0000
#define PROXIMITY25_PS_CONF2_PS_MPS_2           0x1000
#define PROXIMITY25_PS_CONF2_PS_MPS_4           0x2000
#define PROXIMITY25_PS_CONF2_PS_MPS_8           0x3000
#define PROXIMITY25_PS_CONF2_PS_MPS_MASK        0x3000
#define PROXIMITY25_PS_CONF2_PS_HG_X1           0x0000
#define PROXIMITY25_PS_CONF2_PS_HG_X2           0x0400
#define PROXIMITY25_PS_CONF2_PS_HG_MASK         0x0400
#define PROXIMITY25_PS_CONF2_PS_SSINT_DIS       0x0000
#define PROXIMITY25_PS_CONF2_PS_SSINT_EN        0x0100
#define PROXIMITY25_PS_CONF2_PS_SSINT_MASK      0x0100
#define PROXIMITY25_PS_CONF2_PS_PERIOD_10_MS    0x0000
#define PROXIMITY25_PS_CONF2_PS_PERIOD_20_MS    0x0040
#define PROXIMITY25_PS_CONF2_PS_PERIOD_40_MS    0x0080
#define PROXIMITY25_PS_CONF2_PS_PERIOD_80_MS    0x00C0
#define PROXIMITY25_PS_CONF2_PS_PERIOD_MASK     0x00C0
#define PROXIMITY25_PS_CONF2_PS_PERS_1          0x0000
#define PROXIMITY25_PS_CONF2_PS_PERS_2          0x0010
#define PROXIMITY25_PS_CONF2_PS_PERS_3          0x0020
#define PROXIMITY25_PS_CONF2_PS_PERS_4          0x0030
#define PROXIMITY25_PS_CONF2_PS_PERS_MASK       0x0030
#define PROXIMITY25_PS_CONF2_PS_INT_DIS         0x0000
#define PROXIMITY25_PS_CONF2_PS_INT_LOGIC_HL    0x0004
#define PROXIMITY25_PS_CONF2_PS_INT_FIRST_HIGH  0x0008
#define PROXIMITY25_PS_CONF2_PS_INT_MASK        0x000C
#define PROXIMITY25_PS_CONF2_PS_SMART_PERS_DIS  0x0000
#define PROXIMITY25_PS_CONF2_PS_SMART_PERS_EN   0x0002
#define PROXIMITY25_PS_CONF2_PS_SMART_PERS_MASK 0x0002
#define PROXIMITY25_PS_CONF2_PS_SD_POWER_ON     0x0000
#define PROXIMITY25_PS_CONF2_PS_SD_SHUT_DOWN    0x0001
#define PROXIMITY25_PS_CONF2_PS_SD_MASK         0x0001
#define PROXIMITY25_PS_CONF2_RESERVED           0x0800

/**
 * @brief Proximity 25 PS_CONF3 register settings.
 * @details Specified PS_CONF3 register settings of Proximity 25 Click driver.
 */
#define PROXIMITY25_PS_CONF3_PS_SC_DIS          0x0000
#define PROXIMITY25_PS_CONF3_PS_SC_EN           0x8000
#define PROXIMITY25_PS_CONF3_PS_SC_MASK         0x8000
#define PROXIMITY25_PS_CONF3_PS_SC_LEVEL_1      0x0000
#define PROXIMITY25_PS_CONF3_PS_SC_LEVEL_2      0x2000
#define PROXIMITY25_PS_CONF3_PS_SC_LEVEL_3      0x4000
#define PROXIMITY25_PS_CONF3_PS_SC_LEVEL_4      0x6000
#define PROXIMITY25_PS_CONF3_PS_SC_LEVEL_MASK   0x6000
#define PROXIMITY25_PS_CONF3_PS_CURRENT_70_MA   0x0000
#define PROXIMITY25_PS_CONF3_PS_CURRENT_95_MA   0x0100
#define PROXIMITY25_PS_CONF3_PS_CURRENT_110_MA  0x0200
#define PROXIMITY25_PS_CONF3_PS_CURRENT_130_MA  0x0300
#define PROXIMITY25_PS_CONF3_PS_CURRENT_170_MA  0x0400
#define PROXIMITY25_PS_CONF3_PS_CURRENT_200_MA  0x0500
#define PROXIMITY25_PS_CONF3_PS_CURRENT_220_MA  0x0600
#define PROXIMITY25_PS_CONF3_PS_CURRENT_240_MA  0x0700
#define PROXIMITY25_PS_CONF3_PS_CURRENT_MASK    0x0700
#define PROXIMITY25_PS_CONF3_PS_MODE_AUTO       0x0000
#define PROXIMITY25_PS_CONF3_PS_MODE_FORCE      0x0040
#define PROXIMITY25_PS_CONF3_PS_MODE_MASK       0x0040
#define PROXIMITY25_PS_CONF3_PS_TRIG_OFF        0x0000
#define PROXIMITY25_PS_CONF3_PS_TRIG_ON         0x0020
#define PROXIMITY25_PS_CONF3_PS_TRIG_MASK       0x0020
#define PROXIMITY25_PS_CONF3_PS_OFFSET_DIS      0x0000
#define PROXIMITY25_PS_CONF3_PS_OFFSET_EN       0x0008
#define PROXIMITY25_PS_CONF3_PS_OFFSET_MASK     0x0008
#define PROXIMITY25_PS_CONF3_PS_SP_INT_DIS      0x0000
#define PROXIMITY25_PS_CONF3_PS_SP_INT_EN       0x0004
#define PROXIMITY25_PS_CONF3_PS_SP_INT_MASK     0x0004
#define PROXIMITY25_PS_CONF3_RESERVED           0x0000

/**
 * @brief Proximity 25 INT_FLAG register settings.
 * @details Specified INT_FLAG register settings of Proximity 25 Click driver.
 */
#define PROXIMITY25_INT_FLAG_PS_SPFLAG          0x1000
#define PROXIMITY25_INT_FLAG_PS_IF_CLOSE        0x0200
#define PROXIMITY25_INT_FLAG_PS_IF_AWAY         0x0100

/**
 * @brief Proximity 25 ID setting.
 * @details Specified ID of Proximity 25 Click driver.
 */
#define PROXIMITY25_DEVICE_ID                   0x0158

/**
 * @brief Proximity 25 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 25 Click driver.
 */
#define PROXIMITY25_DEVICE_ADDRESS              0x60

/*! @} */ // proximity25_set

/**
 * @defgroup proximity25_map Proximity 25 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 25 Click driver.
 */

/**
 * @addtogroup proximity25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 25 Click to the selected MikroBUS.
 */
#define PROXIMITY25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity25_map
/*! @} */ // proximity25

/**
 * @brief Proximity 25 Click context object.
 * @details Context object definition of Proximity 25 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;                       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} proximity25_t;

/**
 * @brief Proximity 25 Click configuration object.
 * @details Configuration object definition of Proximity 25 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;                         /**< Interrupt pin. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} proximity25_cfg_t;

/**
 * @brief Proximity 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY25_OK = 0,
    PROXIMITY25_ERROR = -1

} proximity25_return_value_t;

/*!
 * @addtogroup proximity25 Proximity 25 Click Driver
 * @brief API for configuring and manipulating Proximity 25 Click driver.
 * @{
 */

/**
 * @brief Proximity 25 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity25_cfg_setup ( proximity25_cfg_t *cfg );

/**
 * @brief Proximity 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity25_init ( proximity25_t *ctx, proximity25_cfg_t *cfg );

/**
 * @brief Proximity 25 default configuration function.
 * @details This function executes a default configuration of Proximity 25
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity25_default_cfg ( proximity25_t *ctx );

/**
 * @brief Proximity 25 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity25_write_reg ( proximity25_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Proximity 25 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity25_read_reg ( proximity25_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Proximity 25 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #proximity25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity25_check_com ( proximity25_t *ctx );

/**
 * @brief Proximity 25 read proximity function.
 * @details This function reads the proximity data.
 * @param[in] ctx : Click context object.
 * See #proximity25_t object definition for detailed explanation.
 * @param[out] ps_data : PS data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity25_read_proximity ( proximity25_t *ctx, uint16_t *ps_data );

/**
 * @brief Proximity 25 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity25_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity25_get_int_pin ( proximity25_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY25_H

/*! @} */ // proximity25

// ------------------------------------------------------------------------ END
