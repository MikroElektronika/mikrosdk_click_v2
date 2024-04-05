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
 * @file thermo30.h
 * @brief This file contains API for Thermo 30 Click Driver.
 */

#ifndef THERMO30_H
#define THERMO30_H

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
 * @addtogroup thermo30 Thermo 30 Click Driver
 * @brief API for configuring and manipulating Thermo 30 Click driver.
 * @{
 */

/**
 * @defgroup thermo30_set Thermo 30 Registers Settings
 * @brief Settings for registers of Thermo 30 Click driver.
 */

/**
 * @addtogroup thermo30_set
 * @{
 */

/**
 * @brief Thermo 30 commands list.
 * @details Specified commands list of Thermo 30 Click driver.
 */
#define THERMO30_CMD_SINGLE_SHOT_CLK_STR_EN_REP_HIGH        0x2C06
#define THERMO30_CMD_SINGLE_SHOT_CLK_STR_EN_REP_MID         0x2C0D
#define THERMO30_CMD_SINGLE_SHOT_CLK_STR_EN_REP_LOW         0x2C10
#define THERMO30_CMD_SINGLE_SHOT_CLK_STR_DIS_REP_HIGH       0x2400
#define THERMO30_CMD_SINGLE_SHOT_CLK_STR_DIS_REP_MID        0x240B
#define THERMO30_CMD_SINGLE_SHOT_CLK_STR_DIS_REP_LOW        0x2416
#define THERMO30_CMD_PERIODIC_0p5_MPS_REP_HIGH              0x2032
#define THERMO30_CMD_PERIODIC_0p5_MPS_REP_MID               0x2024
#define THERMO30_CMD_PERIODIC_0p5_MPS_REP_LOW               0x202F
#define THERMO30_CMD_PERIODIC_1_MPS_REP_HIGH                0x2130
#define THERMO30_CMD_PERIODIC_1_MPS_REP_MID                 0x2126
#define THERMO30_CMD_PERIODIC_1_MPS_REP_LOW                 0x212D
#define THERMO30_CMD_PERIODIC_2_MPS_REP_HIGH                0x2236
#define THERMO30_CMD_PERIODIC_2_MPS_REP_MID                 0x2220
#define THERMO30_CMD_PERIODIC_2_MPS_REP_LOW                 0x222B
#define THERMO30_CMD_PERIODIC_4_MPS_REP_HIGH                0x2334
#define THERMO30_CMD_PERIODIC_4_MPS_REP_MID                 0x2322
#define THERMO30_CMD_PERIODIC_4_MPS_REP_LOW                 0x2329
#define THERMO30_CMD_PERIODIC_10_MPS_REP_HIGH               0x2737
#define THERMO30_CMD_PERIODIC_10_MPS_REP_MID                0x2721
#define THERMO30_CMD_PERIODIC_10_MPS_REP_LOW                0x272A
#define THERMO30_CMD_FETCH_DATA                             0xE000
#define THERMO30_CMD_BREAK                                  0x3093
#define THERMO30_CMD_SOFT_RESET                             0x30A2
#define THERMO30_CMD_HEATER_ENABLE                          0x306D
#define THERMO30_CMD_HEATER_DISABLE                         0x3066
#define THERMO30_CMD_READ_STATUS                            0xF32D
#define THERMO30_CMD_CLEAR_STATUS                           0x3041
#define THERMO30_CMD_GET_SERIAL_NUM                         0x3780

/**
 * @brief Thermo 30 pin state values.
 * @details Specified pin state values of Thermo 30 Click driver.
 */
#define THERMO30_PIN_STATE_HIGH                             0x01
#define THERMO30_PIN_STATE_LOW                              0x00

/**
 * @brief Thermo 30 temperature calculation values.
 * @details Specified temperature calculation values of Thermo 30 Click driver.
 */
#define THERMO30_DATA_RESOLUTION                            65535.0f
#define THERMO30_ABS_MIN_TEMP                               -45.0f
#define THERMO30_ABS_MAX_TEMP                               175.0f

/**
 * @brief Thermo 30 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 30 Click driver.
 */
#define THERMO30_DEVICE_ADDRESS_GND                         0x4A
#define THERMO30_DEVICE_ADDRESS_VCC                         0x4B

/*! @} */ // thermo30_set

/**
 * @defgroup thermo30_map Thermo 30 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 30 Click driver.
 */

/**
 * @addtogroup thermo30_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 30 Click to the selected MikroBUS.
 */
#define THERMO30_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermo30_map
/*! @} */ // thermo30

/**
 * @brief Thermo 30 Click context object.
 * @details Context object definition of Thermo 30 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */

    // Input pins
    digital_in_t alr;           /**< Alert pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} thermo30_t;

/**
 * @brief Thermo 30 Click configuration object.
 * @details Configuration object definition of Thermo 30 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t alr;             /**< Alert pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} thermo30_cfg_t;

/**
 * @brief Thermo 30 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO30_OK = 0,
    THERMO30_ERROR = -1

} thermo30_return_value_t;

/*!
 * @addtogroup thermo30 Thermo 30 Click Driver
 * @brief API for configuring and manipulating Thermo 30 Click driver.
 * @{
 */

/**
 * @brief Thermo 30 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo30_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo30_cfg_setup ( thermo30_cfg_t *cfg );

/**
 * @brief Thermo 30 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo30_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo30_init ( thermo30_t *ctx, thermo30_cfg_t *cfg );

/**
 * @brief Thermo 30 default configuration function.
 * @details This function executes a default configuration of Thermo 30
 * click board.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo30_default_cfg ( thermo30_t *ctx );

/**
 * @brief Thermo 30 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void thermo30_set_rst_pin ( thermo30_t *ctx, uint8_t pin_state );

/**
 * @brief Thermo 30 hw reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void thermo30_hw_reset ( thermo30_t *ctx );

/**
 * @brief Thermo 30 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thermo30_get_alert_pin ( thermo30_t *ctx );

/**
 * @brief Thermo 30 write command function.
 * @details This function writes a desired command by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo30_write_command ( thermo30_t *ctx, uint16_t cmd );

/**
 * @brief Thermo 30 read command function.
 * @details This function writes a desired command word and then reads it's 
 * response word with CRC byte. If the read CRC byte matches internal 
 * CRC calculation the response word will be stored in data_out.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be written.
 * @param[out] data_out : Read response word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo30_read_command ( thermo30_t *ctx, uint16_t cmd, uint16_t *data_out );

/**
 * @brief Thermo 30 start measurement function.
 * @details This function starts the measurements by sending the specified command.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @param[in] cmd : Single-shot or periodic measurements command,
 *                  refer to the commands list macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo30_start_measurement ( thermo30_t *ctx, uint16_t cmd );

/**
 * @brief Thermo 30 stop measurement function.
 * @details This function stops the measurements by sending the break command.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo30_stop_measurement ( thermo30_t *ctx );

/**
 * @brief Thermo 30 read status function.
 * @details This function reads the status register.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @param[out] status_val : Status register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo30_read_status ( thermo30_t *ctx, uint16_t *status_val );

/**
 * @brief Thermo 30 read temperature function.
 * @details This function reads the temperature raw data measurements 
 * and converts it to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo30_t object definition for detailed explanation.
 * @param[out] temperature : Temperature measurements in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo30_read_temperature ( thermo30_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // THERMO30_H

/*! @} */ // thermo30

// ------------------------------------------------------------------------ END
