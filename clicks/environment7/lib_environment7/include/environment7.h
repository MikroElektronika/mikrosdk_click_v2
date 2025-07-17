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
 * @file environment7.h
 * @brief This file contains API for Environment 7 Click Driver.
 */

#ifndef ENVIRONMENT7_H
#define ENVIRONMENT7_H

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
 * @addtogroup environment7 Environment 7 Click Driver
 * @brief API for configuring and manipulating Environment 7 Click driver.
 * @{
 */

/**
 * @defgroup environment7_reg Environment 7 Registers List
 * @brief List of registers of Environment 7 Click driver.
 */

/**
 * @addtogroup environment7_reg
 * @{
 */

/**
 * @brief Environment 7 STCC4 commands list.
 * @details Specified STCC4 commands list of Environment 7 Click driver.
 */
#define ENVIRONMENT7_CMD_START_CONT_MEASUREMENT         0x218B
#define ENVIRONMENT7_CMD_STOP_CONT_MEASUREMENT          0x3F86
#define ENVIRONMENT7_CMD_READ_MEASUREMENT               0xEC05
#define ENVIRONMENT7_CMD_PERFORM_FORCED_RECALIB         0x362F
#define ENVIRONMENT7_CMD_SET_RHT_COMPENSATION           0xE000
#define ENVIRONMENT7_CMD_SET_PRESSURE_COMPENSATION      0xE016
#define ENVIRONMENT7_CMD_MEASURE_SINGLE_SHOT            0x219D
#define ENVIRONMENT7_CMD_ENTER_SLEEP_MODE               0x3650
#define ENVIRONMENT7_CMD_ENABLE_TESTING_MODE            0x3FBC
#define ENVIRONMENT7_CMD_DISABLE_TESTING_MODE           0x3F3D
#define ENVIRONMENT7_CMD_PERFORM_CONDITIONING           0x29BC
#define ENVIRONMENT7_CMD_PERFORM_SELF_TEST              0x278C
#define ENVIRONMENT7_CMD_PERFORM_FACTORY_RESET          0x3632
#define ENVIRONMENT7_CMD_GET_PRODUCT_ID                 0x365B

/*! @} */ // environment7_reg

/**
 * @defgroup environment7_set Environment 7 Registers Settings
 * @brief Settings for registers of Environment 7 Click driver.
 */

/**
 * @addtogroup environment7_set
 * @{
 */

/**
 * @brief Environment 7 STCC4 measurement mode settings.
 * @details Specified STCC4 measurement mode settings of Environment 7 Click driver.
 */
#define ENVIRONMENT7_MEAS_MODE_START_CONTINUOUS         0
#define ENVIRONMENT7_MEAS_MODE_STOP_CONTINUOUS          1
#define ENVIRONMENT7_MEAS_MODE_START_SINGLE_SHOT        2

/**
 * @brief Environment 7 STCC4 measurement calculation values.
 * @details Specified STCC4 measurement calculation values of Environment 7 Click driver.
 */
#define ENVIRONMENT7_PRESSURE_RES                       2
#define ENVIRONMENT7_MAX_RH                             100.0
#define ENVIRONMENT7_MIN_RH                             0.0
#define ENVIRONMENT7_DATA_RESOLUTION                    65535.0
#define ENVIRONMENT7_ABS_MIN_TEMP                       ( -45.0 )
#define ENVIRONMENT7_ABS_MAX_TEMP                       ( 130.0 )
#define ENVIRONMENT7_ABS_MIN_HUM                        ( -6.0 )
#define ENVIRONMENT7_ABS_MAX_HUM                        ( 119.0 )

/**
 * @brief Environment 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Environment 7 Click driver.
 */
#define ENVIRONMENT7_DEVICE_ADDRESS_0                   0x64
#define ENVIRONMENT7_DEVICE_ADDRESS_1                   0x65
#define ENVIRONMENT7_DEVICE_ADDRESS                     ENVIRONMENT7_DEVICE_ADDRESS_1

/*! @} */ // environment7_set

/**
 * @defgroup environment7_map Environment 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Environment 7 Click driver.
 */

/**
 * @addtogroup environment7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Environment 7 Click to the selected MikroBUS.
 */
#define ENVIRONMENT7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // environment7_map
/*! @} */ // environment7

/**
 * @brief Environment 7 Click context object.
 * @details Context object definition of Environment 7 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} environment7_t;

/**
 * @brief Environment 7 Click configuration object.
 * @details Configuration object definition of Environment 7 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} environment7_cfg_t;

/**
 * @brief Environment 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ENVIRONMENT7_OK = 0,
    ENVIRONMENT7_ERROR = -1

} environment7_return_value_t;

/*!
 * @addtogroup environment7 Environment 7 Click Driver
 * @brief API for configuring and manipulating Environment 7 Click driver.
 * @{
 */

/**
 * @brief Environment 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #environment7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void environment7_cfg_setup ( environment7_cfg_t *cfg );

/**
 * @brief Environment 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #environment7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment7_init ( environment7_t *ctx, environment7_cfg_t *cfg );

/**
 * @brief Environment 7 send command function.
 * @details This function sends a command word to the STCC4 device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment7_send_cmd ( environment7_t *ctx, uint16_t cmd );

/**
 * @brief Environment 7 send command with data function.
 * @details This function sends a command along with data to the STCC4 device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be sent.
 * @param[in] data_in : Data words to be written.
 * @param[in] len : Number of data words to be written (up to 2 words).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment7_send_cmd_data ( environment7_t *ctx, uint16_t cmd, uint16_t *data_in, uint8_t len );

/**
 * @brief Environment 7 read data function.
 * @details This function reads measurement data from the STCC4 device.
 * @param[in] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to store the read data.
 * @param[in] len : Number of words to read (up to 6 words).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment7_read_data ( environment7_t *ctx, uint16_t *data_out, uint8_t len );

/**
 * @brief Environment 7 read device id function.
 * @details This function reads the product and serial numbers of the STCC4 device.
 * @param[in] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[out] prod_num : Pointer to store the product number.
 * @param[out] serial_num_msb : Pointer to store the MSB part of the serial number.
 * @param[out] serial_num_lsb : Pointer to store the LSB part of the serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment7_read_id ( environment7_t *ctx, uint32_t *prod_num, uint32_t *serial_num_msb, uint32_t *serial_num_lsb );

/**
 * @brief Environment 7 set RHT function.
 * @details This function sets the temperature and relative humidity compensation value on the STCC4 device.
 * @param[in] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[in] temp : Temperature value in degrees Celsius.
 * @param[in] hum : Humidity value in percentage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment7_set_rht ( environment7_t *ctx, float temp, float hum );

/**
 * @brief Environment 7 set pressure function.
 * @details This function sets the pressure compensation value on the STCC4 device.
 * @param[in] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[in] pressure : Pressure value in Pa.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment7_set_pressure ( environment7_t *ctx, uint32_t pressure );

/**
 * @brief Environment 7 set measurement mode function.
 * @details This function sets the measurement mode on the STCC4 device.
 * @param[in] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[in] mode : Measurement mode selection @li @c 0 - Start continuous measurement mode,
                                                @li @c 1 - Stop continuous measurement mode,
                                                @li @c 2 - Start single shot measurement mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment7_set_meas_mode ( environment7_t *ctx, uint8_t mode );

/**
 * @brief Environment 7 read measurement function.
 * @details This function reads gas concentration, temperature, and relative humidity data from the STCC4 device.
 * @param[in] ctx : Click context object.
 * See #environment7_t object definition for detailed explanation.
 * @param[out] gas : Pointer to store CO2 gas concentration in ppm.
 * @param[out] temp : Pointer to store temperature in degrees Celsius.
 * @param[out] hum : Pointer to store humidity in percentage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment7_read_meas ( environment7_t *ctx, uint16_t *gas, float *temp, float *hum );

#ifdef __cplusplus
}
#endif
#endif // ENVIRONMENT7_H

/*! @} */ // environment7

// ------------------------------------------------------------------------ END
