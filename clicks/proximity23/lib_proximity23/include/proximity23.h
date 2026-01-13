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
 * @file proximity23.h
 * @brief This file contains API for Proximity 23 Click Driver.
 */

#ifndef PROXIMITY23_H
#define PROXIMITY23_H

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
 * @addtogroup proximity23 Proximity 23 Click Driver
 * @brief API for configuring and manipulating Proximity 23 Click driver.
 * @{
 */

/**
 * @defgroup proximity23_reg Proximity 23 Registers List
 * @brief List of registers of Proximity 23 Click driver.
 */

/**
 * @addtogroup proximity23_reg
 * @{
 */

/**
 * @brief Proximity 23 registers list.
 * @details Specified registers list of Proximity 23 Click driver.
 */
#define PROXIMITY23_REG_PS_CONF1                0x00
#define PROXIMITY23_REG_PS_CONF2                0x03
#define PROXIMITY23_REG_PS_CONF3                0x04
#define PROXIMITY23_REG_PS_THDL                 0x05
#define PROXIMITY23_REG_PS_THDH                 0x06
#define PROXIMITY23_REG_PS_CANC                 0x07
#define PROXIMITY23_REG_PS_CONF4                0x08
#define PROXIMITY23_REG_PS_DATA                 0xF8
#define PROXIMITY23_REG_INT_FLAG                0xF9
#define PROXIMITY23_REG_ID                      0xFA
#define PROXIMITY23_REG_PS_AC_DATA              0xFB

/*! @} */ // proximity23_reg

/**
 * @defgroup proximity23_set Proximity 23 Registers Settings
 * @brief Settings for registers of Proximity 23 Click driver.
 */

/**
 * @addtogroup proximity23_set
 * @{
 */
 
/**
 * @brief Proximity 23 PS_CONF1 register settings.
 * @details Specified PS_CONF1 register settings of Proximity 23 Click driver.
 */
#define PROXIMITY23_PS_CONF1_PS_CAL_DIS         0x0000
#define PROXIMITY23_PS_CONF1_PS_CAL_EN          0x0080
#define PROXIMITY23_PS_CONF1_PS_CAL_MASK        0x0080
#define PROXIMITY23_PS_CONF1_PS_ON_DIS          0x0000
#define PROXIMITY23_PS_CONF1_PS_ON_EN           0x0002
#define PROXIMITY23_PS_CONF1_PS_ON_MASK         0x0002
#define PROXIMITY23_PS_CONF1_RESERVED           0x0201

/**
 * @brief Proximity 23 PS_CONF2 register settings.
 * @details Specified PS_CONF2 register settings of Proximity 23 Click driver.
 */
#define PROXIMITY23_PS_CONF2_PS_IT_1T           0x0000
#define PROXIMITY23_PS_CONF2_PS_IT_2T           0x4000
#define PROXIMITY23_PS_CONF2_PS_IT_4T           0x8000
#define PROXIMITY23_PS_CONF2_PS_IT_8T           0xC000
#define PROXIMITY23_PS_CONF2_PS_IT_MASK         0xC000
#define PROXIMITY23_PS_CONF2_PS_MPS_1           0x0000
#define PROXIMITY23_PS_CONF2_PS_MPS_2           0x1000
#define PROXIMITY23_PS_CONF2_PS_MPS_4           0x2000
#define PROXIMITY23_PS_CONF2_PS_MPS_8           0x3000
#define PROXIMITY23_PS_CONF2_PS_MPS_MASK        0x3000
#define PROXIMITY23_PS_CONF2_PS_ITB_25_US       0x0000
#define PROXIMITY23_PS_CONF2_PS_ITB_50_US       0x0800
#define PROXIMITY23_PS_CONF2_PS_ITB_MASK        0x0800
#define PROXIMITY23_PS_CONF2_PS_GAIN_DIS        0x0000
#define PROXIMITY23_PS_CONF2_PS_GAIN_EN         0x0400
#define PROXIMITY23_PS_CONF2_PS_GAIN_MASK       0x0400
#define PROXIMITY23_PS_CONF2_PS_PERIOD_10_MS    0x0000
#define PROXIMITY23_PS_CONF2_PS_PERIOD_20_MS    0x0040
#define PROXIMITY23_PS_CONF2_PS_PERIOD_40_MS    0x0080
#define PROXIMITY23_PS_CONF2_PS_PERIOD_80_MS    0x00C0
#define PROXIMITY23_PS_CONF2_PS_PERIOD_MASK     0x00C0
#define PROXIMITY23_PS_CONF2_PS_PERS_1          0x0000
#define PROXIMITY23_PS_CONF2_PS_PERS_2          0x0010
#define PROXIMITY23_PS_CONF2_PS_PERS_3          0x0020
#define PROXIMITY23_PS_CONF2_PS_PERS_4          0x0030
#define PROXIMITY23_PS_CONF2_PS_PERS_MASK       0x0030
#define PROXIMITY23_PS_CONF2_PS_INT_DIS         0x0000
#define PROXIMITY23_PS_CONF2_PS_INT_LOGIC_HL    0x0004
#define PROXIMITY23_PS_CONF2_PS_INT_FIRST_HIGH  0x0008
#define PROXIMITY23_PS_CONF2_PS_INT_EN          0x000C
#define PROXIMITY23_PS_CONF2_PS_INT_MASK        0x000C
#define PROXIMITY23_PS_CONF2_PS_SMART_PERS_DIS  0x0000
#define PROXIMITY23_PS_CONF2_PS_SMART_PERS_EN   0x0002
#define PROXIMITY23_PS_CONF2_PS_SMART_PERS_MASK 0x0002
#define PROXIMITY23_PS_CONF2_PS_ST_START        0x0000
#define PROXIMITY23_PS_CONF2_PS_ST_STOP         0x0001
#define PROXIMITY23_PS_CONF2_PS_ST_MASK         0x0001
#define PROXIMITY23_PS_CONF2_RESERVED           0x0000

/**
 * @brief Proximity 23 PS_CONF3 register settings.
 * @details Specified PS_CONF3 register settings of Proximity 23 Click driver.
 */
#define PROXIMITY23_PS_CONF3_PS_SC_DIS          0x0000
#define PROXIMITY23_PS_CONF3_PS_SC_EN           0xE000
#define PROXIMITY23_PS_CONF3_PS_SC_MASK         0xE000
#define PROXIMITY23_PS_CONF3_PS_HD_12_BITS      0x0000
#define PROXIMITY23_PS_CONF3_PS_HD_16_BITS      0x1000
#define PROXIMITY23_PS_CONF3_PS_HD_MASK         0x1000
#define PROXIMITY23_PS_CONF3_I_VCSEL_8_MA       0x0100
#define PROXIMITY23_PS_CONF3_I_VCSEL_10_MA      0x0200
#define PROXIMITY23_PS_CONF3_I_VCSEL_12_MA      0x0300
#define PROXIMITY23_PS_CONF3_I_VCSEL_14_MA      0x0400
#define PROXIMITY23_PS_CONF3_I_VCSEL_16_MA      0x0500
#define PROXIMITY23_PS_CONF3_I_VCSEL_18_MA      0x0600
#define PROXIMITY23_PS_CONF3_I_VCSEL_20_MA      0x0700
#define PROXIMITY23_PS_CONF3_I_VCSEL_MASK       0x0700
#define PROXIMITY23_PS_CONF3_PS_AF_AUTO         0x0000
#define PROXIMITY23_PS_CONF3_PS_AF_FORCE        0x0040
#define PROXIMITY23_PS_CONF3_PS_AF_MASK         0x0040
#define PROXIMITY23_PS_CONF3_PS_FOR_TRIG_OFF    0x0000
#define PROXIMITY23_PS_CONF3_PS_FOR_TRIG_ON     0x0020
#define PROXIMITY23_PS_CONF3_PS_FOR_TRIG_MASK   0x0020
#define PROXIMITY23_PS_CONF3_PS_FORCENUM_ONE    0x0000
#define PROXIMITY23_PS_CONF3_PS_FORCENUM_TWO    0x0010
#define PROXIMITY23_PS_CONF3_PS_FORCENUM_MASK   0x0010
#define PROXIMITY23_PS_CONF3_PS_SP_INT_DIS      0x0000
#define PROXIMITY23_PS_CONF3_PS_SP_INT_EN       0x0004
#define PROXIMITY23_PS_CONF3_PS_SP_INT_MASK     0x0004
#define PROXIMITY23_PS_CONF3_RESERVED           0x0008

/**
 * @brief Proximity 23 PS_CONF4 register settings.
 * @details Specified PS_CONF4 register settings of Proximity 23 Click driver.
 */
#define PROXIMITY23_PS_CONF4_PS_LPPER_40_MS     0x0000
#define PROXIMITY23_PS_CONF4_PS_LPPER_80_MS     0x0200
#define PROXIMITY23_PS_CONF4_PS_LPPER_160_MS    0x0400
#define PROXIMITY23_PS_CONF4_PS_LPPER_320_MS    0x0600
#define PROXIMITY23_PS_CONF4_PS_LPPER_MASK      0x0600
#define PROXIMITY23_PS_CONF4_PS_LPEN_DIS        0x0000
#define PROXIMITY23_PS_CONF4_PS_LPEN_EN         0x0100
#define PROXIMITY23_PS_CONF4_PS_LPEN_MASK       0x0100
#define PROXIMITY23_PS_CONF4_PS_AC_PERIOD_3_MS  0x0000
#define PROXIMITY23_PS_CONF4_PS_AC_PERIOD_6_MS  0x0040
#define PROXIMITY23_PS_CONF4_PS_AC_PERIOD_12_MS 0x0080
#define PROXIMITY23_PS_CONF4_PS_AC_PERIOD_24_MS 0x00C0
#define PROXIMITY23_PS_CONF4_PS_AC_PERIOD_MASK  0x00C0
#define PROXIMITY23_PS_CONF4_PS_AC_NUM_1        0x0000
#define PROXIMITY23_PS_CONF4_PS_AC_NUM_2        0x0010
#define PROXIMITY23_PS_CONF4_PS_AC_NUM_4        0x0020
#define PROXIMITY23_PS_CONF4_PS_AC_NUM_8        0x0030
#define PROXIMITY23_PS_CONF4_PS_AC_NUM_MASK     0x0030
#define PROXIMITY23_PS_CONF4_PS_AC_DIS          0x0000
#define PROXIMITY23_PS_CONF4_PS_AC_EN           0x0008
#define PROXIMITY23_PS_CONF4_PS_AC_MASK         0x0008
#define PROXIMITY23_PS_CONF4_PS_AC_TRIG_DIS     0x0000
#define PROXIMITY23_PS_CONF4_PS_AC_TRIG_EN      0x0004
#define PROXIMITY23_PS_CONF4_PS_AC_TRIG_MASK    0x0004
#define PROXIMITY23_PS_CONF4_PS_AC_INT_DIS      0x0000
#define PROXIMITY23_PS_CONF4_PS_AC_INT_EN       0x0001
#define PROXIMITY23_PS_CONF4_PS_AC_INT_MASK     0x0001
#define PROXIMITY23_PS_CONF4_RESERVED           0x0000

/**
 * @brief Proximity 23 INT_FLAG register settings.
 * @details Specified INT_FLAG register settings of Proximity 23 Click driver.
 */
#define PROXIMITY23_INT_FLAG_PS_ACFLAG          0x2000
#define PROXIMITY23_INT_FLAG_PS_SPFLAG          0x1000
#define PROXIMITY23_INT_FLAG_PS_IF_CLOSE        0x0200
#define PROXIMITY23_INT_FLAG_PS_IF_AWAY         0x0100

/**
 * @brief Proximity 23 ID setting.
 * @details Specified ID of Proximity 23 Click driver.
 */
#define PROXIMITY23_DEVICE_ID                   0x0026

/**
 * @brief Proximity 23 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 23 Click driver.
 */
#define PROXIMITY23_DEVICE_ADDRESS              0x60

/*! @} */ // proximity23_set

/**
 * @defgroup proximity23_map Proximity 23 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 23 Click driver.
 */

/**
 * @addtogroup proximity23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 23 Click to the selected MikroBUS.
 */
#define PROXIMITY23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity23_map
/*! @} */ // proximity23

/**
 * @brief Proximity 23 Click context object.
 * @details Context object definition of Proximity 23 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} proximity23_t;

/**
 * @brief Proximity 23 Click configuration object.
 * @details Configuration object definition of Proximity 23 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} proximity23_cfg_t;

/**
 * @brief Proximity 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY23_OK = 0,
    PROXIMITY23_ERROR = -1

} proximity23_return_value_t;

/*!
 * @addtogroup proximity23 Proximity 23 Click Driver
 * @brief API for configuring and manipulating Proximity 23 Click driver.
 * @{
 */

/**
 * @brief Proximity 23 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity23_cfg_setup ( proximity23_cfg_t *cfg );

/**
 * @brief Proximity 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity23_init ( proximity23_t *ctx, proximity23_cfg_t *cfg );

/**
 * @brief Proximity 23 default configuration function.
 * @details This function executes a default configuration of Proximity 23
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity23_default_cfg ( proximity23_t *ctx );

/**
 * @brief Proximity 23 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity23_write_reg ( proximity23_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Proximity 23 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity23_read_reg ( proximity23_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Proximity 23 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity23_check_com ( proximity23_t *ctx );

/**
 * @brief Proximity 23 read proximity function.
 * @details This function reads the proximity data.
 * @param[in] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @param[out] ps_data : PS data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity23_read_proximity ( proximity23_t *ctx, uint16_t *ps_data );

/**
 * @brief Proximity 23 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity23_enable_device ( proximity23_t *ctx );

/**
 * @brief Proximity 23 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity23_disable_device ( proximity23_t *ctx );

/**
 * @brief Proximity 23 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity23_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity23_get_int_pin ( proximity23_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY23_H

/*! @} */ // proximity23

// ------------------------------------------------------------------------ END
