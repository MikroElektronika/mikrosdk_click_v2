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
 * @file pressure22.h
 * @brief This file contains API for Pressure 22 Click Driver.
 */

#ifndef PRESSURE22_H
#define PRESSURE22_H

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
 * @addtogroup pressure22 Pressure 22 Click Driver
 * @brief API for configuring and manipulating Pressure 22 Click driver.
 * @{
 */

/**
 * @defgroup pressure22_cmd Pressure 22 Commands List
 * @brief List of commands of Pressure 22 Click driver.
 */

/**
 * @addtogroup pressure22_cmd
 * @{
 */

/**
 * @brief Pressure 22 description command.
 * @details Specified command for description of Pressure 22 Click driver.
 */
#define PRESSURE22_CMD_ADC_READ                  0x00
#define PRESSURE22_CMD_RESET                     0x1E
#define PRESSURE22_CMD_PROM_VERSION              0xA0
#define PRESSURE22_CMD_PROM_READ_C1              0xA2
#define PRESSURE22_CMD_PROM_READ_C2              0xA4
#define PRESSURE22_CMD_PROM_READ_C3              0xA6
#define PRESSURE22_CMD_PROM_READ_C4              0xA8
#define PRESSURE22_CMD_PROM_READ_C5              0xAA
#define PRESSURE22_CMD_PROM_READ_C6              0xAC
#define PRESSURE22_CMD_PROM_END                  0xAE

/*! @} */ // pressure22_cmd

/**
 * @defgroup pressure22_set Pressure 22 Registers Settings
 * @brief Settings for registers of Pressure 22 Click driver.
 */

/**
 * @addtogroup pressure22_set
 * @{
 */

/**
 * @brief Pressure 22 bit mask.
 * @details Specified bit mask of Pressure 22 Click driver.
 */
#define PRESSURE22_CRC4_BIT_MASK                 0x000Fu
#define PRESSURE22_VER_DEF_BIT_MASK              0x007Fu
#define PRESSURE22_FCT_DEF_BIT_MASK              0x001Fu

/**
 * @brief Pressure 22 calculation coefficients.
 * @details Specified calculation coefficients of Pressure 22 Click driver.
 */
#define PRESSURE22_TEMPERATURE_20_C              40.0f
#define PRESSURE22_TEMPERATURE_10_C              10.0f
#define PRESSURE22_TEMP_TYPICAL                  2000.0f
#define PRESSURE22_TEMP_DIV                      100.0f
#define PRESSURE22_OFF_ACT_TEMP_MULTP            131072.0f
#define PRESSURE22_OFF_ACT_TEMP_DIV              64.0f
#define PRESSURE22_SENS_ACT_TEMP_MULTP           65536.0f
#define PRESSURE22_SENS_ACT_TEMP_DIV             128.0f
#define PRESSURE22_TEMP_COMP_PRESS_DIV           2097152.0f
#define PRESSURE22_COMP_PRESS_DIV                32768.0f
#define PRESSURE22_PRESS_CONVERT_PA_MBAR         100.0f
#define PRESSURE22_SEC_COMP_TI_DIV               34359738368.0f
#define PRESSURE22_SEC_COMP_TI_1_MULTP           14.0f
#define PRESSURE22_SEC_COMP_OFFI_1_MULTP         35.0f
#define PRESSURE22_SEC_COMP_SENS_MULTP           63.0f
#define PRESSURE22_SEC_COMP_OFFI_1_DIV           8.0f
#define PRESSURE22_SEC_COMP_TI_2_MULTP           12.0f
#define PRESSURE22_SEC_COMP_OFFI_2_MULTP         30.0f
#define PRESSURE22_SEC_COMP_OFFI_2_DIV           256.0f
#define PRESSURE22_SEC_COMP_SENSI_DIV            32.0f

/**
 * @brief Pressure 22 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 22 Click driver.
 */
#define PRESSURE22_DEVICE_ADDRESS                0x76

/*! @} */ // pressure22_set

/**
 * @defgroup pressure22_map Pressure 22 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 22 Click driver.
 */

/**
 * @addtogroup pressure22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 22 Click to the selected MikroBUS.
 */
#define PRESSURE22_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // pressure22_map
/*! @} */ // pressure22

/**
 * @brief Pressure 22 Click pressure conversion value data.
 * @details Predefined enum values for pressure conversion values.
 */
typedef enum
{
    PRESSURE22_CMD_PRESS_OSR_256  = 0x40,
    PRESSURE22_CMD_PRESS_OSR_512  = 0x42,
    PRESSURE22_CMD_PRESS_OSR_1024 = 0x44,
    PRESSURE22_CMD_PRESS_OSR_2048 = 0x46,
    PRESSURE22_CMD_PRESS_OSR_4096 = 0x48,
    PRESSURE22_CMD_PRESS_OSR_8192 = 0x4A

} pressure22_press_conv_t;

/**
 * @brief Pressure 22 Click temperature conversion value data.
 * @details Predefined enum values for temperature conversion values.
 */
typedef enum
{
    PRESSURE22_CMD_TEMP_OSR_256  = 0x50,
    PRESSURE22_CMD_TEMP_OSR_512  = 0x52,
    PRESSURE22_CMD_TEMP_OSR_1024 = 0x54,
    PRESSURE22_CMD_TEMP_OSR_2048 = 0x56,
    PRESSURE22_CMD_TEMP_OSR_4096 = 0x58,
    PRESSURE22_CMD_TEMP_OSR_8192 = 0x5A

} pressure22_temp_conv_t;

/**
 * @brief Pressure 22 Click context object.
 * @details Context object definition of Pressure 22 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
    
    // Calibration data (factory calibrated) from PROM
    uint16_t   prom_pt;       /**< Product type. */
    uint8_t    prom_crc;      /**< 4-bit CRC. */
    uint8_t    prom_ver;      /**< Version defined. */
    uint8_t    prom_fct;      /**< Factory defined. */
    uint16_t   prom_c1;       /**< Pressure sensitivity | SENST1. */
    uint16_t   prom_c2;       /**< Pressure offset | OFFT1. */
    uint16_t   prom_c3;       /**< Temperature coefficient of pressure sensitivity | TCS. */
    uint16_t   prom_c4;       /**< Temperature coefficient of pressure offset | TCO. */
    uint16_t   prom_c5;       /**< Reference temperature | TREF. */
    uint16_t   prom_c6;       /**< Temperature coefficient of the temperature | TEMPSENS. */
    
    // Conversions
    pressure22_press_conv_t    press_conv;    /**< Pressure conversion. */
    pressure22_temp_conv_t     temp_conv;     /**< Temperature conversion. */

} pressure22_t;

/**
 * @brief Pressure 22 Click configuration object.
 * @details Configuration object definition of Pressure 22 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} pressure22_cfg_t;

/**
 * @brief Pressure 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE22_OK = 0,
    PRESSURE22_ERROR = -1

} pressure22_return_value_t;

/*!
 * @addtogroup pressure22 Pressure 22 Click Driver
 * @brief API for configuring and manipulating Pressure 22 Click driver.
 * @{
 */

/**
 * @brief Pressure 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure22_cfg_setup ( pressure22_cfg_t *cfg );

/**
 * @brief Pressure 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_init ( pressure22_t *ctx, pressure22_cfg_t *cfg );

/**
 * @brief Pressure 22 default configuration function.
 * @details This function executes a default configuration of Pressure 22
 * click board.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pressure22_default_cfg ( pressure22_t *ctx );

/**
 * @brief Pressure 22 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_generic_write ( pressure22_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 22 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_generic_read ( pressure22_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 22 set the command function.
 * @details This function writes the desired command
 * of the MS5839-02BA, Ultra-compact, chlorine resistant,
 * digital pressure and temperature sensor
 * on the Pressure 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_set_command ( pressure22_t *ctx, uint8_t cmd );

/**
 * @brief Pressure 22 sw reset function.
 * @details This function performs the software reset
 * of the MS5839-02BA, Ultra-compact, chlorine resistant,
 * digital pressure and temperature sensor
 * on the Pressure 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_sw_reset ( pressure22_t *ctx );

/**
 * @brief Pressure 22 gets the ADC data function.
 * @details This function reads temperature or pressure ADC data
 * of the MS5839-02BA, Ultra-compact, chlorine resistant,
 * digital pressure and temperature sensor
 * on the Pressure 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @param[out] adc : ADC read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_get_adc_data ( pressure22_t *ctx, uint32_t *adc );

/**
 * @brief Pressure 22 gets the PROM data function.
 * @details This function reads calibration data,
 * factory calibrated from the PROM memory
 * of the MS5839-02BA, Ultra-compact, chlorine resistant,
 * digital pressure and temperature sensor
 * on the Pressure 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @param[in] cmd_prom : PROM command.
 * @param[out] prom : PROM read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_get_prom_data ( pressure22_t *ctx, uint8_t cmd_prom, uint16_t *prom );

/**
 * @brief Pressure 22 gets the calibration data function.
 * @details This function reads and store calibration data,
 * factory calibrated from the PROM memory 
 * of the MS5839-02BA, Ultra-compact, chlorine resistant,
 * digital pressure and temperature sensor
 * on the Pressure 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_get_calibration_data ( pressure22_t *ctx );

/**
 * @brief Pressure 22 checks data validity function.
 * @details This function checks CRC to check the data validity in memory
 * of the MS5839-02BA, Ultra-compact, chlorine resistant,
 * digital pressure and temperature sensor
 * on the Pressure 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_check_data_validity ( pressure22_t *ctx );

/**
 * @brief Pressure 22 set conversion function.
 * @details This function sets the desired temperature and pressure data conversion
 * of the MS5839-02BA, Ultra-compact, chlorine resistant,
 * digital pressure and temperature sensor
 * on the Pressure 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @param[in] press_conv : Pressure conversion object.
 * See pressure22_press_conv_t definition for detailed explanation.
 * @param[in] temp_conv : Temperature conversion object.
 * See pressure22_temp_conv_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void pressure22_set_conversion ( pressure22_t *ctx, pressure22_press_conv_t press_conv, 
                                                    pressure22_temp_conv_t temp_conv );

/**
 * @brief Pressure 22 get the measurement data function.
 * @details This function reads temperature and pressure data conversion
 * of the MS5839-02BA, Ultra-compact, chlorine resistant,
 * digital pressure and temperature sensor
 * on the Pressure 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure22_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data ( degree Celsius ).
 * @param[out] pressure : Pressure data ( mbar ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure22_get_measurement_data ( pressure22_t *ctx, float *temperature, float *pressure );



#ifdef __cplusplus
}
#endif
#endif // PRESSURE22_H

/*! @} */ // pressure22

// ------------------------------------------------------------------------ END
