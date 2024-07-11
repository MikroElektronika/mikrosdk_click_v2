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
 * @file temphum25.h
 * @brief This file contains API for TempHum 25 Click Driver.
 */

#ifndef TEMPHUM25_H
#define TEMPHUM25_H

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
 * @addtogroup temphum25 TempHum 25 Click Driver
 * @brief API for configuring and manipulating TempHum 25 Click driver.
 * @{
 */

/**
 * @defgroup temphum25_reg TempHum 25 Registers List
 * @brief List of registers of TempHum 25 Click driver.
 */

/**
 * @addtogroup temphum25_reg
 * @{
 */

/**
 * @brief TempHum 25 command list.
 * @details Specified command list of TempHum 25 Click driver.
 */
#define TEMPHUM25_CMD_MEAS_SSH_REP_HIGH_CS_EN           0x2C06
#define TEMPHUM25_CMD_MEAS_SSH_REP_MID_CS_EN            0x2C0D
#define TEMPHUM25_CMD_MEAS_SSH_REP_LOW_CS_EN            0x2C10
#define TEMPHUM25_CMD_MEAS_SSH_REP_HIGH_CS_DIS          0x2400
#define TEMPHUM25_CMD_MEAS_SSH_REP_MID_CS_DIS           0x240B
#define TEMPHUM25_CMD_MEAS_SSH_REP_LOW_CS_DIS           0x2416
#define TEMPHUM25_CMD_MEAS_CONT_REP_HIGH_MPS_0_5        0x2032
#define TEMPHUM25_CMD_MEAS_CONT_REP_MID_MPS_0_5         0x2024
#define TEMPHUM25_CMD_MEAS_CONT_REP_LOW_MPS_0_5         0x202F
#define TEMPHUM25_CMD_MEAS_CONT_REP_HIGH_MPS_1          0x2130
#define TEMPHUM25_CMD_MEAS_CONT_REP_MID_MPS_1           0x2126
#define TEMPHUM25_CMD_MEAS_CONT_REP_LOW_MPS_1           0x212D
#define TEMPHUM25_CMD_MEAS_CONT_REP_HIGH_MPS_2          0x2236
#define TEMPHUM25_CMD_MEAS_CONT_REP_MID_MPS_2           0x2220
#define TEMPHUM25_CMD_MEAS_CONT_REP_LOW_MPS_2           0x222B
#define TEMPHUM25_CMD_MEAS_CONT_REP_HIGH_MPS_4          0x2334
#define TEMPHUM25_CMD_MEAS_CONT_REP_MID_MPS_4           0x2322
#define TEMPHUM25_CMD_MEAS_CONT_REP_LOW_MPS_4           0x2329
#define TEMPHUM25_CMD_MEAS_CONT_REP_HIGH_MPS_10         0x2737
#define TEMPHUM25_CMD_MEAS_CONT_REP_MID_MPS_10          0x2721
#define TEMPHUM25_CMD_MEAS_CONT_REP_LOW_MPS_10          0x272A
#define TEMPHUM25_CMD_MEAS_CONT_ART                     0x2B32
#define TEMPHUM25_CMD_CONT_MEAS_STOP                    0x3093
#define TEMPHUM25_CMD_FETCH_DATA                        0xE000
#define TEMPHUM25_CMD_SOFT_RESET                        0x30A2
#define TEMPHUM25_CMD_HEATER_ENABLE                     0x306D
#define TEMPHUM25_CMD_HEATER_DISABLE                    0x3066
#define TEMPHUM25_CMD_GET_SERIAL_NUM_0                  0x3780
#define TEMPHUM25_CMD_GET_SERIAL_NUM_1                  0x3682
#define TEMPHUM25_CMD_READ_STATUS                       0xF32D
#define TEMPHUM25_CMD_CLEAR_STATUS                      0x3041

/*! @} */ // temphum25_reg

/**
 * @defgroup temphum25_set TempHum 25 Registers Settings
 * @brief Settings for registers of TempHum 25 Click driver.
 */

/**
 * @addtogroup temphum25_set
 * @{
 */

/**
 * @brief TempHum 25 temperature and humidity calculation values.
 * @details Specified temperature and humidity calculation values of TempHum 25 Click driver.
 */
#define TEMPHUM25_MAX_RH                                100.0f
#define TEMPHUM25_MIN_RH                                0.0f
#define TEMPHUM25_DATA_RESOLUTION                       65535.0f
#define TEMPHUM25_ABS_MIN_TEMP                          ( -45.0f )
#define TEMPHUM25_ABS_MAX_TEMP                          ( 130.0f )

/**
 * @brief TempHum 25 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 25 Click driver.
 */
#define TEMPHUM25_DEVICE_ADDRESS_0                      0x44
#define TEMPHUM25_DEVICE_ADDRESS_1                      0x45

/*! @} */ // temphum25_set

/**
 * @defgroup temphum25_map TempHum 25 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 25 Click driver.
 */

/**
 * @addtogroup temphum25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 25 Click to the selected MikroBUS.
 */
#define TEMPHUM25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // temphum25_map
/*! @} */ // temphum25

/**
 * @brief TempHum 25 Click context object.
 * @details Context object definition of TempHum 25 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */

    // Input pins
    digital_in_t alert;         /**< Alert pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} temphum25_t;

/**
 * @brief TempHum 25 Click configuration object.
 * @details Configuration object definition of TempHum 25 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t alert;           /**< Alert pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} temphum25_cfg_t;

/**
 * @brief TempHum 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM25_OK = 0,
    TEMPHUM25_ERROR = -1

} temphum25_return_value_t;

/*!
 * @addtogroup temphum25 TempHum 25 Click Driver
 * @brief API for configuring and manipulating TempHum 25 Click driver.
 * @{
 */

/**
 * @brief TempHum 25 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum25_cfg_setup ( temphum25_cfg_t *cfg );

/**
 * @brief TempHum 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_init ( temphum25_t *ctx, temphum25_cfg_t *cfg );

/**
 * @brief TempHum 25 send command function.
 * @details This function sends the selected command word by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_send_command ( temphum25_t *ctx, uint16_t cmd );

/**
 * @brief TempHum 25 start measurement function.
 * @details This function starts the measurement by sending the selected measurement command.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @param[in] meas_cmd : Measurement command word to be written.
 * See #TEMPHUM25_CMD_MEAS_x macros definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_start_measurement ( temphum25_t *ctx, uint16_t meas_cmd );

/**
 * @brief TempHum 25 stop measurement function.
 * @details This function stops the continuous measurement.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_stop_measurement ( temphum25_t *ctx );

/**
 * @brief TempHum 25 read measurement function.
 * @details This function reads the temperature and humidity measurements results.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @param[out] temperature : Temperature measurement result in degrees Celsius.
 * @param[out] humidity : Relative humidity measurement result in percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_read_measurement ( temphum25_t *ctx, float *temperature, float *humidity );

/**
 * @brief TempHum 25 read serial num function.
 * @details This function reads the 4-bytes unique serial number by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @param[out] serial_num : 4-bytes unique serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_read_serial_num ( temphum25_t *ctx, uint32_t *serial_num );

/**
 * @brief TempHum 25 read status function.
 * @details This function reads the 2-bytes status register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @param[out] status : 2-bytes status register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_read_status ( temphum25_t *ctx, uint16_t *status );

/**
 * @brief TempHum 25 clear status function.
 * @details This function clears the status register.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_clear_status ( temphum25_t *ctx );

/**
 * @brief TempHum 25 enable heater function.
 * @details This function enables the internal heater.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_enable_heater ( temphum25_t *ctx );

/**
 * @brief TempHum 25 disable heater function.
 * @details This function disables the internal heater.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_disable_heater ( temphum25_t *ctx );

/**
 * @brief TempHum 25 soft reset function.
 * @details This function performs the software reset by sending the soft reset command.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum25_soft_reset ( temphum25_t *ctx );

/**
 * @brief TempHum 25 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void temphum25_set_rst_pin ( temphum25_t *ctx, uint8_t state );

/**
 * @brief TempHum 25 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum25_reset_device ( temphum25_t *ctx );

/**
 * @brief TempHum 25 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #temphum25_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t temphum25_get_alert_pin ( temphum25_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM25_H

/*! @} */ // temphum25

// ------------------------------------------------------------------------ END
