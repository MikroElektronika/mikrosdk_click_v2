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
 * @file barometer4.h
 * @brief This file contains API for Barometer 4 Click Driver.
 */

#ifndef BAROMETER4_H
#define BAROMETER4_H

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
 * @addtogroup barometer4 Barometer 4 Click Driver
 * @brief API for configuring and manipulating Barometer 4 Click driver.
 * @{
 */

/**
 * @defgroup barometer4_reg Barometer 4 Command List
 * @brief List of command of Barometer 4 Click driver.
 */

/**
 * @addtogroup barometer4_cmd
 * @{
 */

/**
 * @brief Barometer 4 description command.
 * @details Specified command for description of Barometer 4 Click driver.
 */
#define BAROMETER4_CMD_OP_MODE_T_FIRST_LOW_POWER           0x609C
#define BAROMETER4_CMD_OP_MODE_T_FIRST_NORMAL              0x6825
#define BAROMETER4_CMD_OP_MODE_T_FIRST_LOW_NOISE           0x70DF
#define BAROMETER4_CMD_OP_MODE_T_FIRST_ULTRA_LOW_NOISE     0x7866
#define BAROMETER4_CMD_OP_MODE_P_FIRST_LOW_POWER           0x401A
#define BAROMETER4_CMD_OP_MODE_P_FIRST_NORMAL              0x48A3
#define BAROMETER4_CMD_OP_MODE_P_FIRST_LOW_NOISE           0x5059
#define BAROMETER4_CMD_OP_MODE_P_FIRST_ULTRA_LOW_NOISE     0x58E0
#define BAROMETER4_CMD_SOFT_RESET                          0x805D
#define BAROMETER4_CMD_DEVICE_ID                           0xEFC8
#define BAROMETER4_CMD_READ_OTP                            0xC7F7

/*! @} */ // barometer4_cmd

/**
 * @defgroup barometer4_set Barometer 4 Registers Settings
 * @brief Settings for registers of Barometer 4 Click driver.
 */

/**
 * @addtogroup barometer4_set
 * @{
 */

/**
 * @brief Barometer 4 description setting.
 * @details Specified setting for description of Barometer 4 Click driver.
 */
#define BAROMETER4_OP_MODE_LOW_POWER                       0
#define BAROMETER4_OP_MODE_NORMAL                          1
#define BAROMETER4_OP_MODE_LOW_NOISE                       2
#define BAROMETER4_OP_MODE_ULTRA_LOW_NOISE                 3

/**
 * @brief Barometer 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 4 Click driver.
 */
#define BAROMETER4_SET_DEV_ADDR                           0x63

/*! @} */ // barometer4_set

/**
 * @defgroup barometer4_map Barometer 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 4 Click driver.
 */

/**
 * @addtogroup barometer4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 4 Click to the selected MikroBUS.
 */
#define BAROMETER4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // barometer4_map
/*! @} */ // barometer4

/**
 * @brief Barometer 4 Click context object.
 * @details Context object definition of Barometer 4 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} barometer4_t;

/**
 * @brief Barometer 4 Click configuration object.
 * @details Configuration object definition of Barometer 4 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} barometer4_cfg_t;

/**
 * @brief Barometer 4 Click structure to hold pressure sensor 
 * related parameters object.
 * @details Structure to hold pressure sensor 
 * related parameters object definition of Barometer 4 Click driver.
 */
typedef struct 
{
    uint16_t op_mode;
    float sensor_constants[ 4 ]; 
    float p_pa_calib[ 3 ];
    float lut_lower;
    float lut_upper;
    float quadr_factor;
    float offst_factor;
    
} barometer4_invpres_t;

/**
 * @brief Barometer 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BAROMETER4_OK = 0,
   BAROMETER4_ERROR = -1

} barometer4_return_value_t;

/*!
 * @addtogroup barometer4 Barometer 4 Click Driver
 * @brief API for configuring and manipulating Barometer 4 Click driver.
 * @{
 */

/**
 * @brief Barometer 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer4_cfg_setup ( barometer4_cfg_t *cfg );

/**
 * @brief Barometer 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_init ( barometer4_t *ctx, barometer4_cfg_t *cfg );

/**
 * @brief Barometer 4 default configuration function.
 * @details This function executes a default configuration of Barometer 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer4_default_cfg ( barometer4_t *ctx );

/**
 * @brief Barometer 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[in] cmd : Commands.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_generic_write ( barometer4_t *ctx, uint16_t cmd, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Barometer 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[in] cmd : Commands.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_generic_read ( barometer4_t *ctx, uint16_t cmd, uint16_t *rx_buf, uint8_t rx_len );

/**
 * @brief Barometer 4 set command function.
 * @details This function sets desired command of the 
 * ICP-10111, High Accuracy, Low Power, Waterproof Barometric Pressure a
 * nd Temperature Sensor IC on the Barometer 4 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_set_command ( barometer4_t *ctx, uint16_t cmd ) ;

/**
 * @brief Barometer 4 software reset function.
 * @details This function performs a software reset of the 
 * ICP-10111, High Accuracy, Low Power, Waterproof Barometric Pressure a
 * nd Temperature Sensor IC on the Barometer 4 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_soft_reset ( barometer4_t *ctx );

/**
 * @brief Barometer 4 get device ID function.
 * @details This function read device ID of the 
 * ICP-10111, High Accuracy, Low Power, Waterproof Barometric Pressure a
 * nd Temperature Sensor IC on the Barometer 4 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[out] device_id : Device ID value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_get_device_id ( barometer4_t *ctx, uint16_t *device_id );

/**
 * @brief Barometer 4 set up OTP read function.
 * @details This function performs a OTP read mode of the 
 * ICP-10111, High Accuracy, Low Power, Waterproof Barometric Pressure a
 * nd Temperature Sensor IC on the Barometer 4 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_set_up_otp_read ( barometer4_t *ctx );

/**
 * @brief Barometer 4 get OTP function.
 * @details This function read OTP values of the 
 * ICP-10111, High Accuracy, Low Power, Waterproof Barometric Pressure a
 * nd Temperature Sensor IC on the Barometer 4 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[out] otp_data : OTP values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_get_otp ( barometer4_t *ctx, uint16_t *otp_data );

/**
 * @brief Barometer 4 inverse process data function.
 * @details This function performs a inverse process data of the 
 * ICP-10111, High Accuracy, Low Power, Waterproof Barometric Pressure a
 * nd Temperature Sensor IC on the Barometer 4 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[in] cfg_data : Data structure to hold pressure sensor related parameters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_inv_invpres_calibration ( barometer4_t *ctx, barometer4_invpres_t *cfg_data );

/**
 * @brief Barometer 4 get RAW data function.
 * @details This function read RAW data of the 
 * ICP-10111, High Accuracy, Low Power, Waterproof Barometric Pressure a
 * nd Temperature Sensor IC on the Barometer 4 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[in] measurement_comd : Operation mode measurement commands.
 * @param[out] pressure : RAW pressure data.
 * @param[out] temperature : RAW temperature data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_get_raw_data ( barometer4_t *ctx, uint16_t measurement_comd, uint32_t *pressure, uint16_t *temperature );

/**
 * @brief Barometer 4 get pressure and temperature function.
 * @details This function read pressure ( Pa ) and temperature ( degree Celsius ) of the 
 * ICP-10111, High Accuracy, Low Power, Waterproof Barometric Pressure a
 * nd Temperature Sensor IC on the Barometer 4 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer4_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data ( Pa ).
 * @param[out] temperature : Temperature data ( degree Celsius ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer4_get_pressure_and_temperature ( barometer4_t *ctx,  float *pressure, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER4_H

/*! @} */ // barometer4

// ------------------------------------------------------------------------ END
