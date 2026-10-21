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
 * @file proximity26.h
 * @brief This file contains API for Proximity 26 Click Driver.
 */

#ifndef PROXIMITY26_H
#define PROXIMITY26_H

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
 * @addtogroup proximity26 Proximity 26 Click Driver
 * @brief API for configuring and manipulating Proximity 26 Click driver.
 * @{
 */

/**
 * @defgroup proximity26_reg Proximity 26 Registers List
 * @brief List of registers of Proximity 26 Click driver.
 */

/**
 * @addtogroup proximity26_reg
 * @{
 */

/**
 * @brief Proximity 26 register list.
 * @details Specified register list of Proximity 26 Click driver.
 */
#define PROXIMITY26_REG_PS_CONF1                0x00
#define PROXIMITY26_REG_PS_CONF2                0x01
#define PROXIMITY26_REG_PS_CONF3                0x02
#define PROXIMITY26_REG_PS_CONF4                0x03
#define PROXIMITY26_REG_PS_THDL                 0x04
#define PROXIMITY26_REG_PS_THDH                 0x05
#define PROXIMITY26_REG_PS_CANC                 0x06
#define PROXIMITY26_REG_PS_CONF5                0x08
#define PROXIMITY26_REG_PS_DATA                 0xF8
#define PROXIMITY26_REG_INT_FLAG                0xF9
#define PROXIMITY26_REG_ID                      0xFA

/*! @} */ // proximity26_reg

/**
 * @defgroup proximity26_set Proximity 26 Registers Settings
 * @brief Settings for registers of Proximity 26 Click driver.
 */

/**
 * @addtogroup proximity26_set
 * @{
 */

/**
 * @brief Proximity 26 PS_CONF1 register settings.
 * @details Specified setting for PS_CONF1 register of Proximity 26 Click driver.
 */
#define PROXIMITY26_PS_CONF1_PS_INT_DIS         0x0000
#define PROXIMITY26_PS_CONF1_PS_INT_LOGIC_HL    0x4000
#define PROXIMITY26_PS_CONF1_PS_INT_FIRST_HIGH  0x8000
#define PROXIMITY26_PS_CONF1_PS_INT_EACH_EVENT  0xC000
#define PROXIMITY26_PS_CONF1_PS_INT_MASK        0xC000
#define PROXIMITY26_PS_CONF1_PS_PERS_1          0x0000
#define PROXIMITY26_PS_CONF1_PS_PERS_2          0x1000
#define PROXIMITY26_PS_CONF1_PS_PERS_3          0x2000
#define PROXIMITY26_PS_CONF1_PS_PERS_4          0x3000
#define PROXIMITY26_PS_CONF1_PS_PERS_MASK       0x3000
#define PROXIMITY26_PS_CONF1_SMART_PERS_DIS     0x0000
#define PROXIMITY26_PS_CONF1_SMART_PERS_EN      0x0800
#define PROXIMITY26_PS_CONF1_SMART_PERS_MASK    0x0800
#define PROXIMITY26_PS_CONF1_PS_SP_INT_DIS      0x0000
#define PROXIMITY26_PS_CONF1_PS_SP_INT_EN       0x0400
#define PROXIMITY26_PS_CONF1_PS_SP_INT_MASK     0x0400
#define PROXIMITY26_PS_CONF1_START_INT_DIS      0x0000
#define PROXIMITY26_PS_CONF1_START_INT_EN       0x0200
#define PROXIMITY26_PS_CONF1_START_INT_MASK     0x0200
#define PROXIMITY26_PS_CONF1_PS_SD_POWER_ON     0x0000
#define PROXIMITY26_PS_CONF1_PS_SD_SHUT_DOWN    0x0100
#define PROXIMITY26_PS_CONF1_PS_SD_MASK         0x0100
#define PROXIMITY26_PS_CONF1_PS_CAL_DIS         0x0000
#define PROXIMITY26_PS_CONF1_PS_CAL_EN          0x0080
#define PROXIMITY26_PS_CONF1_PS_CAL_MASK        0x0080
#define PROXIMITY26_PS_CONF1_PS_TRIG_OFF        0x0000
#define PROXIMITY26_PS_CONF1_PS_TRIG_ON         0x0020
#define PROXIMITY26_PS_CONF1_PS_TRIG_MASK       0x0020
#define PROXIMITY26_PS_CONF1_PS_MODE_AUTO       0x0000
#define PROXIMITY26_PS_CONF1_PS_MODE_FORCE      0x0010
#define PROXIMITY26_PS_CONF1_PS_MODE_MASK       0x0010
#define PROXIMITY26_PS_CONF1_PS_ON_DIS          0x0000
#define PROXIMITY26_PS_CONF1_PS_ON_EN           0x0001
#define PROXIMITY26_PS_CONF1_PS_ON_MASK         0x0001
#define PROXIMITY26_PS_CONF1_RESERVED           0x0000

/**
 * @brief Proximity 26 PS_CONF2 register settings.
 * @details Specified setting for PS_CONF2 register of Proximity 26 Click driver.
 */
#define PROXIMITY26_PS_CONF2_PS_IT_12_5_US      0x0000
#define PROXIMITY26_PS_CONF2_PS_IT_25_US        0x0100
#define PROXIMITY26_PS_CONF2_PS_IT_50_US        0x0200
#define PROXIMITY26_PS_CONF2_PS_IT_75_US        0x0300
#define PROXIMITY26_PS_CONF2_PS_IT_100_US       0x0400
#define PROXIMITY26_PS_CONF2_PS_IT_125_US       0x0500
#define PROXIMITY26_PS_CONF2_PS_IT_150_US       0x0600
#define PROXIMITY26_PS_CONF2_PS_IT_175_US       0x0700
#define PROXIMITY26_PS_CONF2_PS_IT_200_US       0x0800
#define PROXIMITY26_PS_CONF2_PS_IT_225_US       0x0900
#define PROXIMITY26_PS_CONF2_PS_IT_250_US       0x0A00
#define PROXIMITY26_PS_CONF2_PS_IT_275_US       0x0B00
#define PROXIMITY26_PS_CONF2_PS_IT_300_US       0x0C00
#define PROXIMITY26_PS_CONF2_PS_IT_325_US       0x0D00
#define PROXIMITY26_PS_CONF2_PS_IT_350_US       0x0E00
#define PROXIMITY26_PS_CONF2_PS_IT_375_US       0x0F00
#define PROXIMITY26_PS_CONF2_PS_IT_MASK         0x0F00
#define PROXIMITY26_PS_CONF2_PS_WAIT_2_5_MS     0x0000
#define PROXIMITY26_PS_CONF2_PS_WAIT_80_MS      0x001F
#define PROXIMITY26_PS_CONF2_PS_WAIT_MAX        0x00FE
#define PROXIMITY26_PS_CONF2_PS_WAIT_MASK       0x00FF
#define PROXIMITY26_PS_CONF2_RESERVED           0x0000

/**
 * @brief Proximity 26 PS_CONF3 register settings.
 * @details Specified setting for PS_CONF3 register of Proximity 26 Click driver.
 */
#define PROXIMITY26_PS_CONF3_PS_HG_X1           0x0000
#define PROXIMITY26_PS_CONF3_PS_HG_X2           0x4000
#define PROXIMITY26_PS_CONF3_PS_HG_MASK         0x4000
#define PROXIMITY26_PS_CONF3_PS_GAIN_X4         0x0000
#define PROXIMITY26_PS_CONF3_PS_GAIN_X2         0x1000
#define PROXIMITY26_PS_CONF3_PS_GAIN_X1         0x2000
#define PROXIMITY26_PS_CONF3_PS_GAIN_MASK       0x3000
#define PROXIMITY26_PS_CONF3_PD3_EN             0x0400
#define PROXIMITY26_PS_CONF3_PD2_EN             0x0200
#define PROXIMITY26_PS_CONF3_PD1_EN             0x0100
#define PROXIMITY26_PS_CONF3_PD_ALL_EN          0x0700
#define PROXIMITY26_PS_CONF3_PD_MASK            0x0700
#define PROXIMITY26_PS_CONF3_DRIVER_DIS         0x0000
#define PROXIMITY26_PS_CONF3_DRIVER_EN          0x0008
#define PROXIMITY26_PS_CONF3_DRIVER_MASK        0x0008
#define PROXIMITY26_PS_CONF3_PS_CURRENT_8_MA    0x0002
#define PROXIMITY26_PS_CONF3_PS_CURRENT_10_MA   0x0003
#define PROXIMITY26_PS_CONF3_PS_CURRENT_12_MA   0x0004
#define PROXIMITY26_PS_CONF3_PS_CURRENT_14_MA   0x0005
#define PROXIMITY26_PS_CONF3_PS_CURRENT_16_MA   0x0006
#define PROXIMITY26_PS_CONF3_PS_CURRENT_18_MA   0x0007
#define PROXIMITY26_PS_CONF3_PS_CURRENT_MASK    0x0007
#define PROXIMITY26_PS_CONF3_RESERVED           0x0000

/**
 * @brief Proximity 26 PS_CONF4 register settings.
 * @details Specified setting for PS_CONF4 register of Proximity 26 Click driver.
 */
#define PROXIMITY26_PS_CONF4_PS_SC_LEVEL_1      0x0000
#define PROXIMITY26_PS_CONF4_PS_SC_LEVEL_2      0x0400
#define PROXIMITY26_PS_CONF4_PS_SC_LEVEL_3      0x0800
#define PROXIMITY26_PS_CONF4_PS_SC_LEVEL_4      0x0C00
#define PROXIMITY26_PS_CONF4_PS_SC_LEVEL_MASK   0x0C00
#define PROXIMITY26_PS_CONF4_PS_SC_DIS          0x0000
#define PROXIMITY26_PS_CONF4_PS_SC_EN           0x0200
#define PROXIMITY26_PS_CONF4_PS_SC_MASK         0x0200

/**
 * @brief Proximity 26 PS_CANC register setting.
 * @details Specified setting for PS_CANC register of Proximity 26 Click driver.
 */
#define PROXIMITY26_PS_CANC_MASK                0x0FFF

/**
 * @brief Proximity 26 PS_CONF5 register setting.
 * @details Specified setting for PS_CONF5 register of Proximity 26 Click driver.
 */
#define PROXIMITY26_PS_CONF5_RESERVED           0x00A0

/**
 * @brief Proximity 26 INT_FLAG register settings.
 * @details Specified setting for INT_FLAG register of Proximity 26 Click driver.
 */
#define PROXIMITY26_INT_FLAG_PS_START           0x0800
#define PROXIMITY26_INT_FLAG_PS_SPFLAG          0x0400
#define PROXIMITY26_INT_FLAG_PS_IF_CLOSE        0x0200
#define PROXIMITY26_INT_FLAG_PS_IF_AWAY         0x0100

/**
 * @brief Proximity 26 ID setting.
 * @details Specified setting for ID of Proximity 26 Click driver.
 */
#define PROXIMITY26_DEVICE_ID                   0x0029
#define PROXIMITY26_DEVICE_ID_MASK              0x00FF

/**
 * @brief Proximity 26 I2C setting.
 * @details Specified setting for I2C of Proximity 26 Click driver.
 */
#define PROXIMITY26_I2C_WRITE_DATA_NUM          3
#define PROXIMITY26_I2C_READ_DATA_NUM           2

/**
 * @brief Proximity 26 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 26 Click driver.
 */
#define PROXIMITY26_DEVICE_ADDRESS_0            0x60
#define PROXIMITY26_DEVICE_ADDRESS_1            0x51
#define PROXIMITY26_DEVICE_ADDRESS              PROXIMITY26_DEVICE_ADDRESS_0

/*! @} */ // proximity26_set

/**
 * @defgroup proximity26_map Proximity 26 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 26 Click driver.
 */

/**
 * @addtogroup proximity26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 26 Click to the selected MikroBUS.
 */
#define PROXIMITY26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity26_map
/*! @} */ // proximity26

/**
 * @brief Proximity 26 Click context object.
 * @details Context object definition of Proximity 26 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;                       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} proximity26_t;

/**
 * @brief Proximity 26 Click configuration object.
 * @details Configuration object definition of Proximity 26 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;                         /**< Interrupt pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} proximity26_cfg_t;

/**
 * @brief Proximity 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY26_OK = 0,
    PROXIMITY26_ERROR = -1

} proximity26_return_value_t;

/*!
 * @addtogroup proximity26 Proximity 26 Click Driver
 * @brief API for configuring and manipulating Proximity 26 Click driver.
 * @{
 */

/**
 * @brief Proximity 26 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity26_cfg_setup ( proximity26_cfg_t *cfg );

/**
 * @brief Proximity 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity26_init ( proximity26_t *ctx, proximity26_cfg_t *cfg );

/**
 * @brief Proximity 26 default configuration function.
 * @details This function executes a default configuration of Proximity 26
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity26_default_cfg ( proximity26_t *ctx );

/**
 * @brief Proximity 26 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity26_write_reg ( proximity26_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Proximity 26 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity26_read_reg ( proximity26_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Proximity 26 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #proximity26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Only the low byte of the ID register is verified since the high byte
 * depends on the selected slave address.
 */
err_t proximity26_check_com ( proximity26_t *ctx );

/**
 * @brief Proximity 26 read proximity function.
 * @details This function reads the raw proximity data.
 * @param[in] ctx : Click context object.
 * See #proximity26_t object definition for detailed explanation.
 * @param[out] ps_data : Proximity data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The proximity data is a relative value, the higher the value
 * the closer the detected object.
 */
err_t proximity26_read_proximity ( proximity26_t *ctx, uint16_t *ps_data );

/**
 * @brief Proximity 26 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity26_t object definition for detailed explanation.
 * @return INT pin logic state.
 * @note None.
 */
uint8_t proximity26_get_int_pin ( proximity26_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY26_H

/*! @} */ // proximity26

// ------------------------------------------------------------------------ END
