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
 * @file proximity24.h
 * @brief This file contains API for Proximity 24 Click Driver.
 */

#ifndef PROXIMITY24_H
#define PROXIMITY24_H

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
 * @addtogroup proximity24 Proximity 24 Click Driver
 * @brief API for configuring and manipulating Proximity 24 Click driver.
 * @{
 */

/**
 * @defgroup proximity24_reg Proximity 24 Registers List
 * @brief List of registers of Proximity 24 Click driver.
 */

/**
 * @addtogroup proximity24_reg
 * @{
 */

/**
 * @brief Proximity 24 registers list.
 * @details Specified registers list of Proximity 24 Click driver.
 */
#define PROXIMITY24_REG_ALS_CONF12              0x00
#define PROXIMITY24_REG_ALS_THDH                0x01
#define PROXIMITY24_REG_ALS_THDL                0x02
#define PROXIMITY24_REG_PS_CONF12               0x03
#define PROXIMITY24_REG_PS_CONF3_MS             0x04
#define PROXIMITY24_REG_PS_CANC                 0x05
#define PROXIMITY24_REG_PS_THDL                 0x06
#define PROXIMITY24_REG_PS_THDH                 0x07
#define PROXIMITY24_REG_PS_DATA                 0x08
#define PROXIMITY24_REG_ALS_DATA                0x0B
#define PROXIMITY24_REG_WHITE_DATA              0x0C
#define PROXIMITY24_REG_INT_FLAG                0x0D
#define PROXIMITY24_REG_ID                      0x0E

/*! @} */ // proximity24_reg

/**
 * @defgroup proximity24_set Proximity 24 Registers Settings
 * @brief Settings for registers of Proximity 24 Click driver.
 */

/**
 * @addtogroup proximity24_set
 * @{
 */

/**
 * @brief Proximity 24 ALS_CONF12 register settings.
 * @details Specified settings for ALS_CONF12 register of Proximity 24 Click driver.
 */
#define PROXIMITY24_ALS_CONF2_ALS_NS_X2             0x0000
#define PROXIMITY24_ALS_CONF2_ALS_NS_X1             0x0200
#define PROXIMITY24_ALS_CONF2_ALS_NS_MASK           0x0200
#define PROXIMITY24_ALS_CONF2_WHITE_SD_POWER_ON     0x0000
#define PROXIMITY24_ALS_CONF2_WHITE_SD_SHUT_DOWN    0x0100
#define PROXIMITY24_ALS_CONF2_WHITE_SD_MASK         0x0100
#define PROXIMITY24_ALS_CONF2_MASK                  0xFF00
#define PROXIMITY24_ALS_CONF1_ALS_IT_50MS           0x0000
#define PROXIMITY24_ALS_CONF1_ALS_IT_100MS          0x0020
#define PROXIMITY24_ALS_CONF1_ALS_IT_200MS          0x0040
#define PROXIMITY24_ALS_CONF1_ALS_IT_400MS          0x0060
#define PROXIMITY24_ALS_CONF1_ALS_IT_800MS          0x0080
#define PROXIMITY24_ALS_CONF1_ALS_IT_MASK           0x00E0
#define PROXIMITY24_ALS_CONF1_ALS_HD_X1             0x0000
#define PROXIMITY24_ALS_CONF1_ALS_HD_X2             0x0010
#define PROXIMITY24_ALS_CONF1_ALS_HD_MASK           0x0010
#define PROXIMITY24_ALS_CONF1_ALS_PERS_1            0x0000
#define PROXIMITY24_ALS_CONF1_ALS_PERS_2            0x0004
#define PROXIMITY24_ALS_CONF1_ALS_PERS_4            0x0008
#define PROXIMITY24_ALS_CONF1_ALS_PERS_8            0x000C
#define PROXIMITY24_ALS_CONF1_ALS_PERS_MASK         0x000C
#define PROXIMITY24_ALS_CONF1_ALS_INT_DIS           0x0000
#define PROXIMITY24_ALS_CONF1_ALS_INT_EN            0x0002
#define PROXIMITY24_ALS_CONF1_ALS_INT_MASK          0x0002
#define PROXIMITY24_ALS_CONF1_ALS_SD_POWER_ON       0x0000
#define PROXIMITY24_ALS_CONF1_ALS_SD_SHUT_DOWN      0x0001
#define PROXIMITY24_ALS_CONF1_ALS_SD_MASK           0x0001
#define PROXIMITY24_ALS_CONF1_MASK                  0x00FF

/**
 * @brief Proximity 24 PS_CONF12 register settings.
 * @details Specified settings for PS_CONF12 register of Proximity 24 Click driver.
 */
#define PROXIMITY24_PS_CONF2_PS_GAIN_TWO_STEP       0x0000
#define PROXIMITY24_PS_CONF2_PS_GAIN_SINGLE_X8      0x2000
#define PROXIMITY24_PS_CONF2_PS_GAIN_SINGLE_X1      0x3000
#define PROXIMITY24_PS_CONF2_PS_GAIN_MASK           0x3000
#define PROXIMITY24_PS_CONF2_PS_HD_12BITS           0x0000
#define PROXIMITY24_PS_CONF2_PS_HD_16BITS           0x0800
#define PROXIMITY24_PS_CONF2_PS_HD_MASK             0x0800
#define PROXIMITY24_PS_CONF2_PS_NS_TWO_STEP_X4      0x0000
#define PROXIMITY24_PS_CONF2_PS_NS_TWO_STEP_X1      0x0400
#define PROXIMITY24_PS_CONF2_PS_NS_MASK             0x0400
#define PROXIMITY24_PS_CONF2_PS_INT_DIS             0x0000
#define PROXIMITY24_PS_CONF2_PS_INT_CLOSE           0x0100
#define PROXIMITY24_PS_CONF2_PS_INT_AWAY            0x0200
#define PROXIMITY24_PS_CONF2_PS_INT_CLOSE_AWAY      0x0300
#define PROXIMITY24_PS_CONF2_PS_INT_MASK            0x0300
#define PROXIMITY24_PS_CONF2_MASK                   0xFF00
#define PROXIMITY24_PS_CONF1_PS_DUTY_1_OF_40        0x0000
#define PROXIMITY24_PS_CONF1_PS_DUTY_1_OF_80        0x0040
#define PROXIMITY24_PS_CONF1_PS_DUTY_1_OF_160       0x0080
#define PROXIMITY24_PS_CONF1_PS_DUTY_1_OF_320       0x00C0
#define PROXIMITY24_PS_CONF1_PS_DUTY_MASK           0x00C0
#define PROXIMITY24_PS_CONF1_PS_PERS_1              0x0000
#define PROXIMITY24_PS_CONF1_PS_PERS_2              0x0010
#define PROXIMITY24_PS_CONF1_PS_PERS_3              0x0020
#define PROXIMITY24_PS_CONF1_PS_PERS_4              0x0030
#define PROXIMITY24_PS_CONF1_PS_PERS_MASK           0x0030
#define PROXIMITY24_PS_CONF1_PS_IT_1T               0x0000
#define PROXIMITY24_PS_CONF1_PS_IT_1_5T             0x0002
#define PROXIMITY24_PS_CONF1_PS_IT_2T               0x0004
#define PROXIMITY24_PS_CONF1_PS_IT_2_5T             0x0006
#define PROXIMITY24_PS_CONF1_PS_IT_3T               0x0008
#define PROXIMITY24_PS_CONF1_PS_IT_3_5T             0x000A
#define PROXIMITY24_PS_CONF1_PS_IT_4T               0x000C
#define PROXIMITY24_PS_CONF1_PS_IT_8T               0x000E
#define PROXIMITY24_PS_CONF1_PS_IT_MASK             0x000E
#define PROXIMITY24_PS_CONF1_PS_SD_POWER_ON         0x0000
#define PROXIMITY24_PS_CONF1_PS_SD_SHUT_DOWN        0x0001
#define PROXIMITY24_PS_CONF1_PS_SD_MASK             0x0001
#define PROXIMITY24_PS_CONF1_MASK                   0x00FF

/**
 * @brief Proximity 24 PS_CONF3_MS register settings.
 * @details Specified settings for PS_CONF3_MS register of Proximity 24 Click driver.
 */
#define PROXIMITY24_PS_MS_PS_SC_CUR_1X              0x0000
#define PROXIMITY24_PS_MS_PS_SC_CUR_2X              0x2000
#define PROXIMITY24_PS_MS_PS_SC_CUR_4X              0x4000
#define PROXIMITY24_PS_MS_PS_SC_CUR_8X              0x6000
#define PROXIMITY24_PS_MS_PS_SC_CUR_MASK            0x6000
#define PROXIMITY24_PS_MS_PS_SP_1X_CAP              0x0000
#define PROXIMITY24_PS_MS_PS_SP_1_5X_CAP            0x1000
#define PROXIMITY24_PS_MS_PS_SP_MASK                0x1000
#define PROXIMITY24_PS_MS_PS_SPO_00H                0x0000
#define PROXIMITY24_PS_MS_PS_SPO_FFH                0x0800
#define PROXIMITY24_PS_MS_PS_SPO_MASK               0x0800
#define PROXIMITY24_PS_MS_LED_I_50MA                0x0000
#define PROXIMITY24_PS_MS_LED_I_75MA                0x0100
#define PROXIMITY24_PS_MS_LED_I_100MA               0x0200
#define PROXIMITY24_PS_MS_LED_I_120MA               0x0300
#define PROXIMITY24_PS_MS_LED_I_140MA               0x0400
#define PROXIMITY24_PS_MS_LED_I_160MA               0x0500
#define PROXIMITY24_PS_MS_LED_I_180MA               0x0600
#define PROXIMITY24_PS_MS_LED_I_200MA               0x0700
#define PROXIMITY24_PS_MS_LED_I_MASK                0x0700
#define PROXIMITY24_PS_MS_MASK                      0xFF00
#define PROXIMITY24_PS_CONF3_LED_I_LOW_DIS          0x0000
#define PROXIMITY24_PS_CONF3_LED_I_LOW_EN           0x0080
#define PROXIMITY24_PS_CONF3_LED_I_LOW_MASK         0x0080
#define PROXIMITY24_PS_CONF3_PS_SMART_PERS_DIS      0x0000
#define PROXIMITY24_PS_CONF3_PS_SMART_PERS_EN       0x0010
#define PROXIMITY24_PS_CONF3_PS_SMART_PERS_MASK     0x0010
#define PROXIMITY24_PS_CONF3_PS_AF_DIS              0x0000
#define PROXIMITY24_PS_CONF3_PS_AF_EN               0x0008
#define PROXIMITY24_PS_CONF3_PS_AF_MASK             0x0008
#define PROXIMITY24_PS_CONF3_PS_TRIG_NO_TRIG        0x0000
#define PROXIMITY24_PS_CONF3_PS_TRIG_ONE_TIME       0x0004
#define PROXIMITY24_PS_CONF3_PS_TRIG_MASK           0x0004
#define PROXIMITY24_PS_CONF3_PS_MS_NORMAL           0x0000
#define PROXIMITY24_PS_CONF3_PS_MS_DET_LOGIC        0x0002
#define PROXIMITY24_PS_CONF3_PS_MS_MASK             0x0002
#define PROXIMITY24_PS_CONF3_PS_SC_EN_TURN_OFF      0x0000
#define PROXIMITY24_PS_CONF3_PS_SC_EN_TURN_ON       0x0001
#define PROXIMITY24_PS_CONF3_PS_SC_EN_MASK          0x0001
#define PROXIMITY24_PS_CONF3_MASK                   0x00FF

/**
 * @brief Proximity 24 INT_FLAG register settings.
 * @details Specified settings for INT_FLAG register of Proximity 24 Click driver.
 */
#define PROXIMITY24_INT_FLAG_ALS_IF_L               0x2000
#define PROXIMITY24_INT_FLAG_ALS_IF_H               0x1000
#define PROXIMITY24_INT_FLAG_PS_SP                  0x0400
#define PROXIMITY24_INT_FLAG_PS_IF_CLOSE            0x0200
#define PROXIMITY24_INT_FLAG_PS_IF_AWAY             0x0100
#define PROXIMITY24_INT_FLAG_MASK                   0xFF00

/**
 * @brief Proximity 24 ALS integration time settings.
 * @details Specified settings for ALS integration time of Proximity 24 Click driver.
 */
#define PROXIMITY24_ALS_IT_50MS                     0
#define PROXIMITY24_ALS_IT_100MS                    1
#define PROXIMITY24_ALS_IT_200MS                    2
#define PROXIMITY24_ALS_IT_400MS                    3
#define PROXIMITY24_ALS_IT_800MS                    4

/**
 * @brief Proximity 24 ALS sensitivity settings.
 * @details Specified settings for ALS sensitivity of Proximity 24 Click driver.
 */
#define PROXIMITY24_ALS_SENS                        0.064

/**
 * @brief Proximity 24 ID setting.
 * @details Specified ID of Proximity 24 Click driver.
 */
#define PROXIMITY24_DEVICE_ID                       0x80
#define PROXIMITY24_DEVICE_ID_MASK                  0xFF

/**
 * @brief Proximity 24 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 24 Click driver.
 */
#define PROXIMITY24_DEVICE_ADDRESS                  0x60

/*! @} */ // proximity24_set

/**
 * @defgroup proximity24_map Proximity 24 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 24 Click driver.
 */

/**
 * @addtogroup proximity24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 24 Click to the selected MikroBUS.
 */
#define PROXIMITY24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity24_map
/*! @} */ // proximity24

/**
 * @brief Proximity 24 Click context object.
 * @details Context object definition of Proximity 24 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float als_sens;             /**< ALS sensitivity. */

} proximity24_t;

/**
 * @brief Proximity 24 Click configuration object.
 * @details Configuration object definition of Proximity 24 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} proximity24_cfg_t;

/**
 * @brief Proximity 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY24_OK = 0,
    PROXIMITY24_ERROR = -1

} proximity24_return_value_t;

/*!
 * @addtogroup proximity24 Proximity 24 Click Driver
 * @brief API for configuring and manipulating Proximity 24 Click driver.
 * @{
 */

/**
 * @brief Proximity 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity24_cfg_setup ( proximity24_cfg_t *cfg );

/**
 * @brief Proximity 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity24_init ( proximity24_t *ctx, proximity24_cfg_t *cfg );

/**
 * @brief Proximity 24 default configuration function.
 * @details This function executes a default configuration of Proximity 24
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity24_default_cfg ( proximity24_t *ctx );

/**
 * @brief Proximity 24 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity24_write_reg ( proximity24_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Proximity 24 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity24_read_reg ( proximity24_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Proximity 24 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity24_check_com ( proximity24_t *ctx );

/**
 * @brief Proximity 24 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity24_get_int_pin ( proximity24_t *ctx );

/**
 * @brief Proximity 24 set ALS integration time function.
 * @details This function sets the ALS integration time and calculates ALS data sensitivity.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @param[out] als_it : ALS integration time, see PROXIMITY24_ALS_IT_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity24_set_als_int_time ( proximity24_t *ctx, uint8_t als_it );

/**
 * @brief Proximity 24 read proximity function.
 * @details This function reads the proximity data.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @param[out] ps_data : PS data sensor output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity24_read_proximity ( proximity24_t *ctx, uint16_t *ps_data );

/**
 * @brief Proximity 24 read ALS data function.
 * @details This function reads the ALS data.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @param[out] als_data : ALS data sensor output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity24_read_als_data ( proximity24_t *ctx, uint16_t *als_data );

/**
 * @brief Proximity 24 read white data function.
 * @details This function reads the white data.
 * @param[in] ctx : Click context object.
 * See #proximity24_t object definition for detailed explanation.
 * @param[out] white_data : White data sensor output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity24_read_white_data ( proximity24_t *ctx, uint16_t *white_data );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY24_H

/*! @} */ // proximity24

// ------------------------------------------------------------------------ END
