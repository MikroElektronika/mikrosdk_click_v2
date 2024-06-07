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
 * @file current12.h
 * @brief This file contains API for Current 12 Click Driver.
 */

#ifndef CURRENT12_H
#define CURRENT12_H

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
 * @addtogroup current12 Current 12 Click Driver
 * @brief API for configuring and manipulating Current 12 Click driver.
 * @{
 */

/**
 * @defgroup current12_reg Current 12 Registers List
 * @brief List of registers of Current 12 Click driver.
 */

/**
 * @addtogroup current12_reg
 * @{
 */

/**
 * @brief Current 12 description register.
 * @details Specified register for description of Current 12 Click driver.
 */
#define CURRENT12_REG_CONFIGURATION           0x00
#define CURRENT12_REG_SHUNT_VOLTAGE           0x01
#define CURRENT12_REG_LOAD_VOLTAGE            0x02
#define CURRENT12_REG_DC_POWER                0x03
#define CURRENT12_REG_CURRENT                 0x04
#define CURRENT12_REG_TEMPERATURE             0x05
#define CURRENT12_REG_MASK                    0x06
#define CURRENT12_REG_FLAG                    0x07
#define CURRENT12_REG_RSHUNT                  0x08
#define CURRENT12_REG_SOL                     0x09
#define CURRENT12_REG_SUL                     0x0A
#define CURRENT12_REG_LOL                     0x0B
#define CURRENT12_REG_LUL                     0x0C
#define CURRENT12_REG_POL                     0x0D
#define CURRENT12_REG_TOL                     0x0E
#define CURRENT12_REG_MANUFACTURING_ID        0xFE
#define CURRENT12_REG_DIE_ID                  0xFF

/*! @} */ // current12_reg

/**
 * @defgroup current12_set Current 12 Registers Settings
 * @brief Settings for registers of Current 12 Click driver.
 */

/**
 * @addtogroup current12_set
 * @{
 */

/**
 * @brief Current 12 description configuration setting.
 * @details Specified configuration setting for description of Current 12 Click driver.
 */
#define CURRENT12_CFG_RST_DISABLE             0x00
#define CURRENT12_CFG_RST_ENABLE              0x01
#define CURRENT12_CFG_RST_BITMASK             0x01
#define CURRENT12_CFG_CT_128_US               0x00
#define CURRENT12_CFG_CT_256_US               0x01
#define CURRENT12_CFG_CT_512_US               0x02
#define CURRENT12_CFG_CT_1024_US              0x03
#define CURRENT12_CFG_CT_2048_US              0x04
#define CURRENT12_CFG_CT_4096_US              0x05
#define CURRENT12_CFG_CT_8192_US              0x06
#define CURRENT12_CFG_CT_16384_US             0x07
#define CURRENT12_CFG_CT_32768_US             0x08
#define CURRENT12_CFG_CT_BITMASK              0x0F
#define CURRENT12_CFG_TEMP_DISABLE            0x00
#define CURRENT12_CFG_TEMP_ENABLE             0x01
#define CURRENT12_CFG_TEMP_BITMASK            0x01
#define CURRENT12_CFG_OP_MODE_SHUTDOWN        0x00
#define CURRENT12_CFG_OP_MODE_SV_TRG          0x01
#define CURRENT12_CFG_OP_MODE_LV_TRG          0x02
#define CURRENT12_CFG_OP_MODE_SLV_TRG         0x03
#define CURRENT12_CFG_OP_MODE_IDLE_MODE       0x04
#define CURRENT12_CFG_OP_MODE_SV_CONT         0x05
#define CURRENT12_CFG_OP_MODE_LV_CONT         0x06
#define CURRENT12_CFG_OP_MODE_SLV_CONT        0x07
#define CURRENT12_CFG_OP_MODE_BITMASK         0x07

/**
 * @brief Current 12 manufacturing ID data value.
 * @details Manufacturing ID data value of Current 12 Click driver.
 */
#define CURRENT12_DEVICE_ID                   0x0006u

/**
 * @brief Current 12 default RSHUNT value.
 * @details Specified configuration setting for description of Current 12 Click driver.
 */
#define CURRENT12_RSHUNT_5_MOHM               5.0f
#define CURRENT12_RSHUNT_MAX                  655.35f

/**
 * @brief Current 12 calculation data values.
 * @details Calculation data values of Current 12 Click driver.
 */
#define CURRENT12_CALC_SHUNT_VTG_MV           0.025f
#define CURRENT12_CALC_LOAD_VTG_V             0.002f
#define CURRENT12_CALC_DC_POWER_W             0.025f
#define CURRENT12_CALC_CURRENT_MA             0.5f
#define CURRENT12_CALC_TEMP_C                 0.5f

/**
 * @brief Current 12 temperature error data bitmask.
 * @details Temperature error bitmask of Current 12 Click driver.
 */
#define CURRENT12_TEMP_ERROR_BITMASK          0x8000u

/**
 * @brief Current 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Current 12 Click driver.
 */
#define CURRENT12_DEVICE_ADDRESS_0            0x40
#define CURRENT12_DEVICE_ADDRESS_1            0x41
#define CURRENT12_DEVICE_ADDRESS_2            0x42
#define CURRENT12_DEVICE_ADDRESS_3            0x43

/*! @} */ // current12_set

/**
 * @defgroup current12_map Current 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 12 Click driver.
 */

/**
 * @addtogroup current12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 12 Click to the selected MikroBUS.
 */
#define CURRENT12_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // current12_map
/*! @} */ // current12

/**
 * @brief Current 12 Click context object.
 * @details Context object definition of Current 12 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alr;         /**< Alert pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} current12_t;

/**
 * @brief Current 12 Click configuration object.
 * @details Configuration object definition of Current 12 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alr;    /**< Alert pin. */

    uint32_t i2c_speed;      /**< I2C serial speed. */
    uint8_t  i2c_address;    /**< I2C slave address. */

} current12_cfg_t;

/**
 * @brief Current 12 Click configuration register object.
 * @details Configuration register object definition of Current 12 Click driver.
 */
typedef struct
{
    uint8_t rst;        /**< System reset. */
    uint8_t ct;         /**< Conversion time. */
    uint8_t temp;       /**< Temperature sensor. */
    uint8_t op_mode;    /**< Operating modes. */

} current12_measure_cfg_t;


/**
 * @brief Current 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENT12_OK = 0,
    CURRENT12_ERROR = -1

} current12_return_value_t;

/*!
 * @addtogroup current12 Current 12 Click Driver
 * @brief API for configuring and manipulating Current 12 Click driver.
 * @{
 */

/**
 * @brief Current 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current12_cfg_setup ( current12_cfg_t *cfg );

/**
 * @brief Current 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_init ( current12_t *ctx, current12_cfg_t *cfg );

/**
 * @brief Current 12 default configuration function.
 * @details This function executes a default configuration of Current 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t current12_default_cfg ( current12_t *ctx );

/**
 * @brief Current 12 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_generic_write ( current12_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Current 12 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_generic_read ( current12_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Current 12 word data writing function.
 * @details This function writes a desired 16-byte data to the selected register
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-byte data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_write_word ( current12_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Current 12 word data reading function.
 * @details This function reads a 16-byte data from the selected register
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 16-byte output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_read_word ( current12_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Current 12 set measurement configuration function.
 * @details This function sets the desired measurement configuration
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[in] measure_cfg : Measurement configuration.
 * See #current12_measure_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_set_measure_cfg ( current12_t *ctx, current12_measure_cfg_t measure_cfg );

/**
 * @brief Current 12 get shunt voltage function.
 * @details This function reads the shunt voltage measurement values [mV]
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[out] shunt_voltage : Shunt voltage data [mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_get_shunt_voltage ( current12_t *ctx, float *shunt_voltage );

/**
 * @brief Current 12 get load voltage function.
 * @details This function reads the load voltage measurement values [V]
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[out] load_voltage : Load voltage data [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_get_load_voltage ( current12_t *ctx, float *load_voltage );

/**
 * @brief Current 12 get DC power function.
 * @details This function reads the DC power measurement values [W]
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[out] load_voltage : Load voltage data [W].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_get_dc_power ( current12_t *ctx, float *dc_power );

/**
 * @brief Current 12 get current function.
 * @details This function reads the current measurement values [mA]
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[out] current : Current data [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_get_current ( current12_t *ctx, float *current );

/**
 * @brief Current 12 get temperature function.
 * @details This function reads the temperature measurement values [degC]
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data [degC].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_get_temperature ( current12_t *ctx, float *temperature );

/**
 * @brief Current 12 set RSHUNT function.
 * @details This function sets the RSHUNT resistor value [mOhm] 
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[in] rshunt_mohm : RSHUNT resistorvalue [mOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_set_rshunt ( current12_t *ctx, float rshunt_mohm );

/**
 * @brief Current 12 get device ID function.
 * @details This function reads the manufacturing ID data value
 * of the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @param[out] device_id : Manufacturing ID [0x0006].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current12_get_device_id ( current12_t *ctx, uint16_t *device_id );

/**
 * @brief Current 12 get interrupt function.
 * @details This function return interrupt signal, states of the INT pin
 * f the TSC1641IQT, 60 V, 16-bit high-precision power monitor with I�C and MIPI I3C interface
 * on the Current 12 Click board.
 * @param[in] ctx : Click context object.
 * See #current12_t object definition for detailed explanation.
 * @return @li @c 0 - Low state,
 *         @li @c 1 - High state.
 * @note None.
 */
uint8_t current12_get_alert ( current12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CURRENT12_H

/*! @} */ // current12

// ------------------------------------------------------------------------ END
