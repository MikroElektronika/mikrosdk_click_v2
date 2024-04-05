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
 * @file thermo26.h
 * @brief This file contains API for Thermo 26 Click Driver.
 */

#ifndef THERMO26_H
#define THERMO26_H

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
 * @addtogroup thermo26 Thermo 26 Click Driver
 * @brief API for configuring and manipulating Thermo 26 Click driver.
 * @{
 */

/**
 * @defgroup thermo26_reg Thermo 26 Registers List
 * @brief List of registers of Thermo 26 Click driver.
 */

/**
 * @addtogroup thermo26_reg
 * @{
 */

/**
 * @brief Thermo 26 commands list.
 * @details Specified commands list of Thermo 26 Click driver.
 */
#define THERMO26_CMD_SINGLE_SHOT_CLK_STR_EN_REP_HIGH        0x2C06
#define THERMO26_CMD_SINGLE_SHOT_CLK_STR_EN_REP_MID         0x2C0D
#define THERMO26_CMD_SINGLE_SHOT_CLK_STR_EN_REP_LOW         0x2C10
#define THERMO26_CMD_SINGLE_SHOT_CLK_STR_DIS_REP_HIGH       0x2400
#define THERMO26_CMD_SINGLE_SHOT_CLK_STR_DIS_REP_MID        0x240B
#define THERMO26_CMD_SINGLE_SHOT_CLK_STR_DIS_REP_LOW        0x2416
#define THERMO26_CMD_PERIODIC_0p5_MPS_REP_HIGH              0x2032
#define THERMO26_CMD_PERIODIC_0p5_MPS_REP_MID               0x2024
#define THERMO26_CMD_PERIODIC_0p5_MPS_REP_LOW               0x202F
#define THERMO26_CMD_PERIODIC_1_MPS_REP_HIGH                0x2130
#define THERMO26_CMD_PERIODIC_1_MPS_REP_MID                 0x2126
#define THERMO26_CMD_PERIODIC_1_MPS_REP_LOW                 0x212D
#define THERMO26_CMD_PERIODIC_2_MPS_REP_HIGH                0x2236
#define THERMO26_CMD_PERIODIC_2_MPS_REP_MID                 0x2220
#define THERMO26_CMD_PERIODIC_2_MPS_REP_LOW                 0x222B
#define THERMO26_CMD_PERIODIC_4_MPS_REP_HIGH                0x2334
#define THERMO26_CMD_PERIODIC_4_MPS_REP_MID                 0x2322
#define THERMO26_CMD_PERIODIC_4_MPS_REP_LOW                 0x2329
#define THERMO26_CMD_PERIODIC_10_MPS_REP_HIGH               0x2737
#define THERMO26_CMD_PERIODIC_10_MPS_REP_MID                0x2721
#define THERMO26_CMD_PERIODIC_10_MPS_REP_LOW                0x272A
#define THERMO26_CMD_FETCH_DATA                             0xE000
#define THERMO26_CMD_BREAK                                  0x3093
#define THERMO26_CMD_SOFT_RESET                             0x30A2
#define THERMO26_CMD_HEATER_ENABLE                          0x306D
#define THERMO26_CMD_HEATER_DISABLE                         0x3066
#define THERMO26_CMD_READ_STATUS                            0xF32D
#define THERMO26_CMD_CLEAR_STATUS                           0x3041
#define THERMO26_CMD_GET_SERIAL_NUM                         0x3780

/*! @} */ // thermo26_reg

/**
 * @defgroup thermo26_set Thermo 26 Registers Settings
 * @brief Settings for registers of Thermo 26 Click driver.
 */

/**
 * @addtogroup thermo26_set
 * @{
 */

/**
 * @brief Thermo 26 temperature calculation values.
 * @details Specified temperature calculation values of Thermo 26 Click driver.
 */
#define THERMO26_DATA_RESOLUTION                            65535.0f
#define THERMO26_ABS_MIN_TEMP                               ( -45.0f )
#define THERMO26_ABS_MAX_TEMP                               ( 130.0f )

/**
 * @brief Thermo 26 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 26 Click driver.
 */
#define THERMO26_DEVICE_ADDRESS_0                           0x4A
#define THERMO26_DEVICE_ADDRESS_1                           0x4B

/*! @} */ // thermo26_set

/**
 * @defgroup thermo26_map Thermo 26 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 26 Click driver.
 */

/**
 * @addtogroup thermo26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 26 Click to the selected MikroBUS.
 */
#define THERMO26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermo26_map
/*! @} */ // thermo26

/**
 * @brief Thermo 26 Click context object.
 * @details Context object definition of Thermo 26 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active low). */

    // Input pins
    digital_in_t alt;           /**< Alert pin - indicates alarm condition. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} thermo26_t;

/**
 * @brief Thermo 26 Click configuration object.
 * @details Configuration object definition of Thermo 26 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t alt;             /**< Alert pin - indicates alarm condition. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} thermo26_cfg_t;

/**
 * @brief Thermo 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO26_OK = 0,
    THERMO26_ERROR = -1

} thermo26_return_value_t;

/*!
 * @addtogroup thermo26 Thermo 26 Click Driver
 * @brief API for configuring and manipulating Thermo 26 Click driver.
 * @{
 */

/**
 * @brief Thermo 26 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo26_cfg_setup ( thermo26_cfg_t *cfg );

/**
 * @brief Thermo 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo26_init ( thermo26_t *ctx, thermo26_cfg_t *cfg );

/**
 * @brief Thermo 26 write command function.
 * @details This function writes a desired command by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo26_write_command ( thermo26_t *ctx, uint16_t cmd );

/**
 * @brief Thermo 26 read command function.
 * @details This function writes a desired command word and then reads its response word with CRC byte.
 * If the read CRC byte matches internal CRC calculation the response word will be stored in @b data_out.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be written.
 * @param[out] data_out : Read response word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo26_read_command ( thermo26_t *ctx, uint16_t cmd, uint16_t *data_out );

/**
 * @brief Thermo 26 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void thermo26_reset_device ( thermo26_t *ctx );

/**
 * @brief Thermo 26 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void thermo26_set_rst_pin ( thermo26_t *ctx, uint8_t state );

/**
 * @brief Thermo 26 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thermo26_get_alert_pin ( thermo26_t *ctx );

/**
 * @brief Thermo 26 read temperature function.
 * @details This function reads the temperature raw data measurements and converts it to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @param[out] temperature : Temperature measurements in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo26_read_temperature ( thermo26_t *ctx, float *temperature );

/**
 * @brief Thermo 26 read serial num function.
 * @details This function reads the 32-bit unique serial number.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @param[out] serial_num : 32-bit unique serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo26_read_serial_num ( thermo26_t *ctx, uint32_t *serial_num );

/**
 * @brief Thermo 26 start measurement function.
 * @details This function starts the measurements by sending the specified command.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @param[in] cmd : Single-shot or periodic measurements command, refer to the commands list macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo26_start_measurement ( thermo26_t *ctx, uint16_t cmd );

/**
 * @brief Thermo 26 stop measurement function.
 * @details This function stops the measurements by sending the break command.
 * @param[in] ctx : Click context object.
 * See #thermo26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo26_stop_measurement ( thermo26_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // THERMO26_H

/*! @} */ // thermo26

// ------------------------------------------------------------------------ END
