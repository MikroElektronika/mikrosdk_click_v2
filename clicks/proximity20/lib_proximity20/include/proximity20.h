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
 * @file proximity20.h
 * @brief This file contains API for Proximity 20 Click Driver.
 */

#ifndef PROXIMITY20_H
#define PROXIMITY20_H

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
 * @addtogroup proximity20 Proximity 20 Click Driver
 * @brief API for configuring and manipulating Proximity 20 Click driver.
 * @{
 */

/**
 * @defgroup proximity20_reg Proximity 20 Registers List
 * @brief List of registers of Proximity 20 Click driver.
 */

/**
 * @addtogroup proximity20_reg
 * @{
 */

/**
 * @brief Proximity 20 registers list.
 * @details Specified registers list of Proximity 20 Click driver.
 */
#define PROXIMITY20_REG_PS_CONF1                0x00
#define PROXIMITY20_REG_PS_CONF2                0x01
#define PROXIMITY20_REG_PS_CONF3                0x02
#define PROXIMITY20_REG_PS_THDL                 0x03
#define PROXIMITY20_REG_PS_THDH                 0x04
#define PROXIMITY20_REG_PS_CANC                 0x05
#define PROXIMITY20_REG_PS_DATA                 0xF8
#define PROXIMITY20_REG_INT_FLAG                0xF9
#define PROXIMITY20_REG_ID                      0xFA

/*! @} */ // proximity20_reg

/**
 * @defgroup proximity20_set Proximity 20 Registers Settings
 * @brief Settings for registers of Proximity 20 Click driver.
 */

/**
 * @addtogroup proximity20_set
 * @{
 */
 
/**
 * @brief Proximity 20 PS_CONF1 register settings.
 * @details Specified PS_CONF1 register settings of Proximity 20 Click driver.
 */
#define PROXIMITY20_PS_CONF1_PS_HD_DIS          0x0000
#define PROXIMITY20_PS_CONF1_PS_HD_EN           0x4000
#define PROXIMITY20_PS_CONF1_PS_HD_MASK         0x4000
#define PROXIMITY20_PS_CONF1_PS_SP_INT_DIS      0x0000
#define PROXIMITY20_PS_CONF1_PS_SP_INT_EN       0x2000
#define PROXIMITY20_PS_CONF1_PS_SP_INT_MASK     0x2000
#define PROXIMITY20_PS_CONF1_PS_SMART_PERS_DIS  0x0000
#define PROXIMITY20_PS_CONF1_PS_SMART_PERS_EN   0x1000
#define PROXIMITY20_PS_CONF1_PS_SMART_PERS_MASK 0x1000
#define PROXIMITY20_PS_CONF1_PS_PERS_1          0x0000
#define PROXIMITY20_PS_CONF1_PS_PERS_2          0x0400
#define PROXIMITY20_PS_CONF1_PS_PERS_3          0x0800
#define PROXIMITY20_PS_CONF1_PS_PERS_4          0x0C00
#define PROXIMITY20_PS_CONF1_PS_PERS_MASK       0x0C00
#define PROXIMITY20_PS_CONF1_PS_INT_DIS         0x0000
#define PROXIMITY20_PS_CONF1_PS_INT_LOGIC_H     0x0100
#define PROXIMITY20_PS_CONF1_PS_INT_TRIG_HL     0x0300
#define PROXIMITY20_PS_CONF1_PS_INT_MASK        0x0300
#define PROXIMITY20_PS_CONF1_PS_CAL_DIS         0x0000
#define PROXIMITY20_PS_CONF1_PS_CAL_EN          0x0080
#define PROXIMITY20_PS_CONF1_PS_CAL_MASK        0x0080
#define PROXIMITY20_PS_CONF1_PS_ON_DIS          0x0000
#define PROXIMITY20_PS_CONF1_PS_ON_EN           0x0001
#define PROXIMITY20_PS_CONF1_PS_ON_MASK         0x0001

/**
 * @brief Proximity 20 PS_CONF2 register settings.
 * @details Specified PS_CONF2 register settings of Proximity 20 Click driver.
 */
#define PROXIMITY20_PS_CONF2_PS_SENS_NORMAL     0x0000
#define PROXIMITY20_PS_CONF2_PS_SENS_HIGH       0x2000
#define PROXIMITY20_PS_CONF2_PS_SENS_MASK       0x2000
#define PROXIMITY20_PS_CONF2_PS_OFFSET_DIS      0x0000
#define PROXIMITY20_PS_CONF2_PS_OFFSET_EN       0x1000
#define PROXIMITY20_PS_CONF2_PS_OFFSET_MASK     0x1000
#define PROXIMITY20_PS_CONF2_PS_CURRENT_7_MA    0x0000
#define PROXIMITY20_PS_CONF2_PS_CURRENT_9_MA    0x0100
#define PROXIMITY20_PS_CONF2_PS_CURRENT_11_MA   0x0200
#define PROXIMITY20_PS_CONF2_PS_CURRENT_12_MA   0x0300
#define PROXIMITY20_PS_CONF2_PS_CURRENT_15_MA   0x0400
#define PROXIMITY20_PS_CONF2_PS_CURRENT_17_MA   0x0500
#define PROXIMITY20_PS_CONF2_PS_CURRENT_19_MA   0x0600
#define PROXIMITY20_PS_CONF2_PS_CURRENT_20_MA   0x0700
#define PROXIMITY20_PS_CONF2_PS_CURRENT_MASK    0x0700
#define PROXIMITY20_PS_CONF2_PS_PERIOD_50_MS    0x0000
#define PROXIMITY20_PS_CONF2_PS_PERIOD_100_MS   0x0040
#define PROXIMITY20_PS_CONF2_PS_PERIOD_200_MS   0x0080
#define PROXIMITY20_PS_CONF2_PS_PERIOD_400_MS   0x00C0
#define PROXIMITY20_PS_CONF2_PS_PERIOD_MASK     0x00C0
#define PROXIMITY20_PS_CONF2_PS_IT_1T           0x0000
#define PROXIMITY20_PS_CONF2_PS_IT_2T           0x0010
#define PROXIMITY20_PS_CONF2_PS_IT_4T           0x0020
#define PROXIMITY20_PS_CONF2_PS_IT_8T           0x0030
#define PROXIMITY20_PS_CONF2_PS_IT_MASK         0x0030
#define PROXIMITY20_PS_CONF2_PS_MPS_1           0x0000
#define PROXIMITY20_PS_CONF2_PS_MPS_2           0x0004
#define PROXIMITY20_PS_CONF2_PS_MPS_4           0x0008
#define PROXIMITY20_PS_CONF2_PS_MPS_8           0x000C
#define PROXIMITY20_PS_CONF2_PS_MPS_MASK        0x000C
#define PROXIMITY20_PS_CONF2_PS_ITB_25_US       0x0000
#define PROXIMITY20_PS_CONF2_PS_ITB_50_US       0x0002
#define PROXIMITY20_PS_CONF2_PS_ITB_MASK        0x0002
#define PROXIMITY20_PS_CONF2_PS_GAIN_X1         0x0000
#define PROXIMITY20_PS_CONF2_PS_GAIN_X2         0x0001
#define PROXIMITY20_PS_CONF2_PS_GAIN_MASK       0x0001

/**
 * @brief Proximity 20 PS_CONF3 register settings.
 * @details Specified PS_CONF3 register settings of Proximity 20 Click driver.
 */
#define PROXIMITY20_PS_CONF3_PS_SPERIOD_DIS     0x0000
#define PROXIMITY20_PS_CONF3_PS_SPERIOD_6_25_MS 0x4000
#define PROXIMITY20_PS_CONF3_PS_SPERIOD_12_5_MS 0x8000
#define PROXIMITY20_PS_CONF3_PS_SPERIOD_25_MS   0xC000
#define PROXIMITY20_PS_CONF3_PS_SPERIOD_MASK    0xC000
#define PROXIMITY20_PS_CONF3_PS_SC_DIS          0x0000
#define PROXIMITY20_PS_CONF3_PS_SC_EN           0x1C00
#define PROXIMITY20_PS_CONF3_PS_SC_MASK         0x1C00
#define PROXIMITY20_PS_CONF3_PS_TRIG_OFF        0x0000
#define PROXIMITY20_PS_CONF3_PS_TRIG_ON         0x0020
#define PROXIMITY20_PS_CONF3_PS_TRIG_MASK       0x0020
#define PROXIMITY20_PS_CONF3_PS_MODE_AUTO       0x0000
#define PROXIMITY20_PS_CONF3_PS_MODE_FORCE      0x0010
#define PROXIMITY20_PS_CONF3_PS_MODE_MASK       0x0010

/**
 * @brief Proximity 20 INT_FLAG register settings.
 * @details Specified INT_FLAG register settings of Proximity 20 Click driver.
 */
#define PROXIMITY20_INT_FLAG_PS_SPFLAG          0x1000
#define PROXIMITY20_INT_FLAG_PS_IF_CLOSE        0x0200
#define PROXIMITY20_INT_FLAG_PS_IF_AWAY         0x0100

/**
 * @brief Proximity 20 ID setting.
 * @details Specified ID of Proximity 20 Click driver.
 */
#define PROXIMITY20_DEVICE_ID_U2                0x0129
#define PROXIMITY20_DEVICE_ID_U3                0x0128

/**
 * @brief Proximity 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 20 Click driver.
 */
#define PROXIMITY20_DEVICE_ADDRESS_U2           0x51
#define PROXIMITY20_DEVICE_ADDRESS_U3           0x60

/*! @} */ // proximity20_set

/**
 * @defgroup proximity20_map Proximity 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 20 Click driver.
 */

/**
 * @addtogroup proximity20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 20 Click to the selected MikroBUS.
 */
#define PROXIMITY20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity20_map
/*! @} */ // proximity20

/**
 * @brief Proximity 20 Click context object.
 * @details Context object definition of Proximity 20 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} proximity20_t;

/**
 * @brief Proximity 20 Click configuration object.
 * @details Configuration object definition of Proximity 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} proximity20_cfg_t;

/**
 * @brief Proximity 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY20_OK = 0,
    PROXIMITY20_ERROR = -1

} proximity20_return_value_t;

/*!
 * @addtogroup proximity20 Proximity 20 Click Driver
 * @brief API for configuring and manipulating Proximity 20 Click driver.
 * @{
 */

/**
 * @brief Proximity 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity20_cfg_setup ( proximity20_cfg_t *cfg );

/**
 * @brief Proximity 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity20_init ( proximity20_t *ctx, proximity20_cfg_t *cfg );

/**
 * @brief Proximity 20 default configuration function.
 * @details This function executes a default configuration of Proximity 20
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity20_default_cfg ( proximity20_t *ctx );

/**
 * @brief Proximity 20 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity20_write_register ( proximity20_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Proximity 20 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity20_read_register ( proximity20_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Proximity 20 set device address function.
 * @details This function sets the device slave address.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @param[in] dev_addr : 0x51 - U2 sensor, 0x60 - U3 sensor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity20_set_device_address ( proximity20_t *ctx, uint8_t dev_addr );

/**
 * @brief Proximity 20 check communication function.
 * @details This function checks the communication by reading and verifying the device ID
 * of U2 and U3 sensors.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity20_check_communication ( proximity20_t *ctx );

/**
 * @brief Proximity 20 read proximity function.
 * @details This function reads the proximity data from U2 and U3 sensors.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @param[out] ps_data_u2 : PS data from U2 sensor.
 * @param[out] ps_data_u3 : PS data from U3 sensor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity20_read_proximity ( proximity20_t *ctx, uint16_t *ps_data_u2, uint16_t *ps_data_u3 );

/**
 * @brief Proximity 20 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity20_enable_device ( proximity20_t *ctx );

/**
 * @brief Proximity 20 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity20_disable_device ( proximity20_t *ctx );

/**
 * @brief Proximity 20 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity20_get_int_pin ( proximity20_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY20_H

/*! @} */ // proximity20

// ------------------------------------------------------------------------ END
