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
 * @file proximity18.h
 * @brief This file contains API for Proximity 18 Click Driver.
 */

#ifndef PROXIMITY18_H
#define PROXIMITY18_H

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
 * @addtogroup proximity18 Proximity 18 Click Driver
 * @brief API for configuring and manipulating Proximity 18 Click driver.
 * @{
 */

/**
 * @defgroup proximity18_reg Proximity 18 Registers List
 * @brief List of registers of Proximity 18 Click driver.
 */

/**
 * @addtogroup proximity18_reg
 * @{
 */

/**
 * @brief Proximity 18 registers list.
 * @details Specified registers list of Proximity 18 Click driver.
 */
#define PROXIMITY18_REG_PS_CONF12               0x03
#define PROXIMITY18_REG_PS_CONF3_MS             0x04
#define PROXIMITY18_REG_PS_CANC                 0x05
#define PROXIMITY18_REG_PS_THDL                 0x06
#define PROXIMITY18_REG_PS_THDH                 0x07
#define PROXIMITY18_REG_PS1_DATA                0x08
#define PROXIMITY18_REG_PS2_DATA                0x09
#define PROXIMITY18_REG_PS3_DATA                0x0A
#define PROXIMITY18_REG_INT_FLAG                0x0D
#define PROXIMITY18_REG_ID                      0x0E

/*! @} */ // proximity18_reg

/**
 * @defgroup proximity18_set Proximity 18 Registers Settings
 * @brief Settings for registers of Proximity 18 Click driver.
 */

/**
 * @addtogroup proximity18_set
 * @{
 */

/**
 * @brief Proximity 18 PS_CONF12 register settings.
 * @details Specified settings for PS_CONF12 register of Proximity 18 Click driver.
 */
#define PROXIMITY18_PS_CONF2_MPX_INT_EN_DIS     0x0000
#define PROXIMITY18_PS_CONF2_MPX_INT_EN_EN      0x8000
#define PROXIMITY18_PS_CONF2_MPX_INT_EN_MASK    0x8000
#define PROXIMITY18_PS_CONF2_MPX_MODE_DIS       0x0000
#define PROXIMITY18_PS_CONF2_MPX_MODE_EN        0x4000
#define PROXIMITY18_PS_CONF2_MPX_MODE_MASK      0x4000
#define PROXIMITY18_PS_CONF2_PS_GAIN_TWO_STEP   0x0000
#define PROXIMITY18_PS_CONF2_PS_GAIN_SINGLE_X8  0x2000
#define PROXIMITY18_PS_CONF2_PS_GAIN_SINGLE_X1  0x3000
#define PROXIMITY18_PS_CONF2_PS_GAIN_MASK       0x3000
#define PROXIMITY18_PS_CONF2_PS_HD_12BITS       0x0000
#define PROXIMITY18_PS_CONF2_PS_HD_16BITS       0x0800
#define PROXIMITY18_PS_CONF2_PS_HD_MASK         0x0800
#define PROXIMITY18_PS_CONF2_PS_NS_MASK         0x0400
#define PROXIMITY18_PS_CONF2_PS_INT_DIS         0x0000
#define PROXIMITY18_PS_CONF2_PS_INT_CLOSE       0x0100
#define PROXIMITY18_PS_CONF2_PS_INT_AWAY        0x0200
#define PROXIMITY18_PS_CONF2_PS_INT_CLOSE_AWAY  0x0300
#define PROXIMITY18_PS_CONF2_PS_INT_MASK        0x0300
#define PROXIMITY18_PS_CONF2_MASK               0xFF00
#define PROXIMITY18_PS_CONF1_PS_DUTY_1_OF_40    0x0000
#define PROXIMITY18_PS_CONF1_PS_DUTY_1_OF_80    0x0040
#define PROXIMITY18_PS_CONF1_PS_DUTY_1_OF_160   0x0080
#define PROXIMITY18_PS_CONF1_PS_DUTY_1_OF_320   0x00C0
#define PROXIMITY18_PS_CONF1_PS_DUTY_MASK       0x00C0
#define PROXIMITY18_PS_CONF1_PS_PERS_1          0x0000
#define PROXIMITY18_PS_CONF1_PS_PERS_2          0x0010
#define PROXIMITY18_PS_CONF1_PS_PERS_3          0x0020
#define PROXIMITY18_PS_CONF1_PS_PERS_4          0x0030
#define PROXIMITY18_PS_CONF1_PS_PERS_MASK       0x0030
#define PROXIMITY18_PS_CONF1_PS_IT_1T           0x0000
#define PROXIMITY18_PS_CONF1_PS_IT_1p5T         0x0002
#define PROXIMITY18_PS_CONF1_PS_IT_2T           0x0004
#define PROXIMITY18_PS_CONF1_PS_IT_2p5T         0x0006
#define PROXIMITY18_PS_CONF1_PS_IT_3T           0x0008
#define PROXIMITY18_PS_CONF1_PS_IT_3p5T         0x000A
#define PROXIMITY18_PS_CONF1_PS_IT_4T           0x000C
#define PROXIMITY18_PS_CONF1_PS_IT_8T           0x000E
#define PROXIMITY18_PS_CONF1_PS_IT_MASK         0x000E
#define PROXIMITY18_PS_CONF1_PS_SD_POWER_ON     0x0000
#define PROXIMITY18_PS_CONF1_PS_SD_SHUT_DOWN    0x0001
#define PROXIMITY18_PS_CONF1_PS_SD_MASK         0x0001
#define PROXIMITY18_PS_CONF1_MASK               0x00FF

/**
 * @brief Proximity 18 PS_CONF3_MS register settings.
 * @details Specified settings for PS_CONF3_MS register of Proximity 18 Click driver.
 */
#define PROXIMITY18_PS_MS_PS_SC_CUR_1X          0x0000
#define PROXIMITY18_PS_MS_PS_SC_CUR_2X          0x2000
#define PROXIMITY18_PS_MS_PS_SC_CUR_4X          0x4000
#define PROXIMITY18_PS_MS_PS_SC_CUR_8X          0x6000
#define PROXIMITY18_PS_MS_PS_SC_CUR_MASK        0x6000
#define PROXIMITY18_PS_MS_PS_SP_1X_CAP          0x0000
#define PROXIMITY18_PS_MS_PS_SP_1p5X_CAP        0x1000
#define PROXIMITY18_PS_MS_PS_SP_MASK            0x1000
#define PROXIMITY18_PS_MS_PS_SPO_00H            0x0000
#define PROXIMITY18_PS_MS_PS_SPO_FFH            0x0800
#define PROXIMITY18_PS_MS_PS_SPO_MASK           0x0800
#define PROXIMITY18_PS_MS_LED_I_50mA            0x0000
#define PROXIMITY18_PS_MS_LED_I_75mA            0x0100
#define PROXIMITY18_PS_MS_LED_I_100mA           0x0200
#define PROXIMITY18_PS_MS_LED_I_120mA           0x0300
#define PROXIMITY18_PS_MS_LED_I_140mA           0x0400
#define PROXIMITY18_PS_MS_LED_I_160mA           0x0500
#define PROXIMITY18_PS_MS_LED_I_180mA           0x0600
#define PROXIMITY18_PS_MS_LED_I_200mA           0x0700
#define PROXIMITY18_PS_MS_LED_I_MASK            0x0700
#define PROXIMITY18_PS_MS_MASK                  0xFF00
#define PROXIMITY18_PS_CONF3_LED_I_LOW_DIS      0x0000
#define PROXIMITY18_PS_CONF3_LED_I_LOW_EN       0x0080
#define PROXIMITY18_PS_CONF3_LED_I_LOW_MASK     0x0080
#define PROXIMITY18_PS_CONF3_IRED_SELECT_IRED1  0x0000
#define PROXIMITY18_PS_CONF3_IRED_SELECT_IRED2  0x0020
#define PROXIMITY18_PS_CONF3_IRED_SELECT_IRED3  0x0040
#define PROXIMITY18_PS_CONF3_IRED_SELECT_MASK   0x0060
#define PROXIMITY18_PS_CONF3_PS_SMART_PERS_DIS  0x0000
#define PROXIMITY18_PS_CONF3_PS_SMART_PERS_EN   0x0010
#define PROXIMITY18_PS_CONF3_PS_SMART_PERS_MASK 0x0010
#define PROXIMITY18_PS_CONF3_PS_AF_DIS          0x0000
#define PROXIMITY18_PS_CONF3_PS_AF_EN           0x0008
#define PROXIMITY18_PS_CONF3_PS_AF_MASK         0x0008
#define PROXIMITY18_PS_CONF3_PS_TRIG_NO_TRIG    0x0000
#define PROXIMITY18_PS_CONF3_PS_TRIG_ONE_TIME   0x0004
#define PROXIMITY18_PS_CONF3_PS_TRIG_MASK       0x0004
#define PROXIMITY18_PS_CONF3_PS_MS_NORMAL       0x0000
#define PROXIMITY18_PS_CONF3_PS_MS_DET_LOGIC    0x0002
#define PROXIMITY18_PS_CONF3_PS_MS_MASK         0x0002
#define PROXIMITY18_PS_CONF3_PS_SC_EN_TURN_OFF  0x0000
#define PROXIMITY18_PS_CONF3_PS_SC_EN_TURN_ON   0x0001
#define PROXIMITY18_PS_CONF3_PS_SC_EN_MASK      0x0001
#define PROXIMITY18_PS_CONF3_MASK               0x00FF

/**
 * @brief Proximity 18 INT_FLAG register settings.
 * @details Specified settings for INT_FLAG register of Proximity 18 Click driver.
 */
#define PROXIMITY18_INT_FLAG_MPX_DATA_READY     0x8000
#define PROXIMITY18_INT_FLAG_PS_SP              0x4000
#define PROXIMITY18_INT_FLAG_PS_IF_CLOSE        0x0200
#define PROXIMITY18_INT_FLAG_PS_IF_AWAY         0x0100
#define PROXIMITY18_INT_FLAG_MASK               0xFF00

/**
 * @brief Proximity 18 ID setting.
 * @details Specified ID of Proximity 18 Click driver.
 */
#define PROXIMITY18_DEVICE_ID                   0x80
#define PROXIMITY18_DEVICE_ID_MASK              0xFF

/**
 * @brief Proximity 18 data ready timeout.
 * @details Specified data ready timeout of Proximity 18 Click driver.
 */
#define PROXIMITY18_DATA_READY_TIMEOUT_MS       5000

/**
 * @brief Proximity 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 18 Click driver.
 */
#define PROXIMITY18_DEVICE_ADDRESS              0x41

/*! @} */ // proximity18_set

/**
 * @defgroup proximity18_map Proximity 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 18 Click driver.
 */

/**
 * @addtogroup proximity18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 18 Click to the selected MikroBUS.
 */
#define PROXIMITY18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity18_map
/*! @} */ // proximity18

/**
 * @brief Proximity 18 Click context object.
 * @details Context object definition of Proximity 18 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */ 

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} proximity18_t;

/**
 * @brief Proximity 18 Click configuration object.
 * @details Configuration object definition of Proximity 18 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;             /**< Interrupt pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} proximity18_cfg_t;

/**
 * @brief Proximity 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY18_OK = 0,
    PROXIMITY18_ERROR = -1

} proximity18_return_value_t;

/*!
 * @addtogroup proximity18 Proximity 18 Click Driver
 * @brief API for configuring and manipulating Proximity 18 Click driver.
 * @{
 */

/**
 * @brief Proximity 18 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity18_cfg_setup ( proximity18_cfg_t *cfg );

/**
 * @brief Proximity 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity18_init ( proximity18_t *ctx, proximity18_cfg_t *cfg );

/**
 * @brief Proximity 18 default configuration function.
 * @details This function executes a default configuration of Proximity 18
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity18_default_cfg ( proximity18_t *ctx );

/**
 * @brief Proximity 18 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity18_write_register ( proximity18_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Proximity 18 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity18_read_register ( proximity18_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Proximity 18 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity18_check_communication ( proximity18_t *ctx );

/**
 * @brief Proximity 18 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity18_get_int_pin ( proximity18_t *ctx );

/**
 * @brief Proximity 18 start measurement function.
 * @details This function starts the measurement by setting the one time trigger bit
 * in the PS_CONF3_MS register.
 * @param[in] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity18_start_measurement ( proximity18_t *ctx );

/**
 * @brief Proximity 18 wait for data ready function.
 * @details This function waits for the MPX data ready interrupt flag.
 * @param[in] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity18_wait_for_data_ready ( proximity18_t *ctx );

/**
 * @brief Proximity 18 read proximity function.
 * @details This function reads the proximity data from all 3 sensors.
 * @param[in] ctx : Click context object.
 * See #proximity18_t object definition for detailed explanation.
 * @param[out] ps1_data : PS1 data from IRED1 sensor.
 * @param[out] ps2_data : PS2 data from IRED2 sensor.
 * @param[out] ps3_data : PS3 data from IRED3 sensor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity18_read_proximity ( proximity18_t *ctx, uint16_t *ps1_data, uint16_t *ps2_data, uint16_t *ps3_data );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY18_H

/*! @} */ // proximity18

// ------------------------------------------------------------------------ END
